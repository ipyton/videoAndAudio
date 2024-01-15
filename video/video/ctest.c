//
//  ctest.c
//  video
//  this file is used to capture the sound and camera
//  Created by chen on 2024/1/15.
//

#include "ctest.h"
#include "include/libswresample/swresample.h"
#include "include/libavutil/frame.h"
#include "include/libavutil/channel_layout.h"
#include <string.h>

static int rec_status = 0;

void set_status(int status) {
    rec_status = status;
}

// encode audio data.
static void encode(AVCodecContext * ctx, 
                   AVFrame * frame,
                   AVPacket * pkt,
                   FILE * output) {
    int ret = 0;
    
    ret = avcodec_send_frame(ctx, frame);
    
    while (ret >= 0) {
        ret = avcodec_receive_packet(ctx, pkt);
        
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
            return;
        } else if (ret < 0) {
            printf("Error, encoding audio frame");
            exit(-1);
        }
        
        fwrite(pkt->data, 1, pkt->size, output);
        fflush(output);
    }
    
    return;
}

//this function is used to open a coder
AVCodecContext * open_coder(void) {
    AVCodec * codec = avcodec_find_encoder_by_name("libfdk_aac");
    
    AVCodecContext * codec_ctx = avcodec_alloc_context3(codec);
    codec_ctx->sample_fmt = AV_SAMPLE_FMT_S16;
    codec_ctx->channel_layout = AV_CH_LAYOUT_STEREO;
    codec_ctx->channels = 2;
    codec_ctx->sample_rate = 44100;
    codec_ctx->bit_rate = 0;
    codec_ctx->profile = FF_PROFILE_AAC_HE_V2;
    
    if (avcodec_open2(codec_ctx, codec, NULL) < 0) {
        return NULL;
    }
    
    
    return codec_ctx;
    
}

static AVFrame * create_frame(void) {
    AVFrame * frame = NULL;
    
    frame = av_frame_alloc();
    if (!frame) {
        printf("Error, No Memory!");
        goto __ERROR;
    }
    
    
    frame -> nb_samples = 512; // sample numbers per frame for single channel.
    frame -> format = AV_SAMPLE_FMT_S16; //storage format
    frame -> channel_layout = AV_CH_LAYOUT_STEREO; // channel layout
    
    av_frame_get_buffer(frame, 0);
    if (!frame->data[0]) {
        printf("failed to allocate frame");
    }
    return frame;
    
__ERROR:
    if (frame) {
        av_frame_free(&frame);
    }
    return NULL;
    
}

AVFormatContext * open_dev(void){
    int ret = 0;
    char errors[1024] = {0,};
    
    AVFormatContext * fmt_ctx = NULL;
    AVDictionary * options = NULL;
    
    char * devicename = ":0";
    
    //capture methods
    const AVInputFormat * iformat = av_find_input_format("avfoundation");
    if ((ret = avformat_open_input(&fmt_ctx, devicename, iformat, &options)) < 0) {
        av_strerror(ret, errors, 1024);
        fprintf(stderr, "Failed to open device, [%d]%s\n", ret, errors);
        return NULL;
    }
    return fmt_ctx;
}

static void alloc_data_4_resample(uint8_t *** src_data,
                                  int * src_linesize,
                                  uint8_t *** dst_data,
                                  int * dst_linesize) {
    
    
    av_samples_alloc_array_and_samples(src_data, src_linesize, 1, 512, AV_SAMPLE_FMT_FLT, 0);
    av_samples_alloc_array_and_samples(dst_data, dst_linesize, 2, 512, AV_SAMPLE_FMT_S16, 0);
    
}

static void free_data_4_resample(uint8_t **src_data, uint8_t **dst_data) {
    // 1D pointer: address->data
    // 2D pointer: address->address->data p[0]->address
    if (src_data) {
        av_freep(src_data);
    }
    av_freep(&src_data);
    
    if (dst_data) {
        av_freep(dst_data);
    }
    av_freep(&dst_data);
}

SwrContext * init_swr(void) {
    SwrContext * swr_ctx = NULL;
    swr_ctx = swr_alloc_set_opts(NULL, AV_CH_LAYOUT_STEREO, AV_SAMPLE_FMT_S16, 44100, AV_CH_LAYOUT_STEREO, AV_SAMPLE_FMT_FLT, 44100, 0, NULL);
    if (swr_init(swr_ctx) < 0) {
        printf("swr cannot be init");
    }
    return swr_ctx;

}

static void read_data_and_encode(AVFormatContext * fmt_ctx, 
                                 AVCodecContext * c_ctx,
                                 SwrContext * swr_ctx,
                                 FILE * outfile) {
    int ret = 0;
    
    //packet
    AVPacket pkt;
    AVFrame * frame = NULL;
    AVPacket * newpkt = NULL;
    
    
    //resample buffer.
    uint8_t **src_data = NULL;
    int src_linesize = 0;
    
    uint8_t **dst_data = NULL;
    int dst_linesize = 0;
    
    frame = create_frame();
    
    if (!frame) {
        printf("cannot create frame");
        goto __ERROR;
    }
    
    if (!newpkt) {
        printf("Error, failed to alloc");
        goto __ERROR;
    }
    alloc_data_4_resample(&src_data, &src_linesize, &dst_data, &dst_linesize);
    
    while ((ret = av_read_frame(fmt_ctx, &pkt)) == 0 && rec_status) {
        memcpy((void*)src_data[0], (void*)pkt.data, pkt.size);
        
        swr_convert(swr_ctx, dst_data, 512, (const uint8_t **) src_data, 512);
        
        
        memcpy((void *) frame->data[0], dst_data[0], dst_linesize);
        
        encode(c_ctx, frame, newpkt, outfile);
        av_packet_unref(&pkt);
    }
    encode(c_ctx, NULL, newpkt, outfile);
    
    
    
__ERROR:
    if (frame) {
        av_frame_free(&frame);
    }
    if (newpkt) {
        av_packet_free(&newpkt);
    }
    free_data_4_resample(src_data, dst_data);
}

void rec_audio(void) {
    av_log_set_level(AV_LOG_DEBUG);
    
    
//    int ret = 0;
//    char errors[1024] = {0,};
//    uint8_t ** dst_data = NULL;
//    uint8_t ** src_data = NULL;
//    
//    int src_linesize = 0;
//    int dst_linesize = 0;
//    
    AVFormatContext * fmt_ctx = NULL;
    AVCodecContext * c_ctx = NULL;
    SwrContext * swrContext = NULL;
    //AVDictionary * options = NULL;

    avdevice_register_all();
    rec_status = 1;
    char * output_path = "/Users";
    FILE * outfile = fopen(output_path, "wb+");
    if (!outfile) {
        printf ("cannot open the file");
        goto __ERROR;
    }
    //open the device and get the context.
    fmt_ctx = open_dev();
    
    if (!fmt_ctx) {
        printf("fail to open device");
        goto __ERROR;
    }
    //open decoder context
    c_ctx = open_coder();
    if (!c_ctx) {
        printf("failed to open coder");
        goto __ERROR;
    }
    
    //init resampling context.
    swrContext = init_swr();
    if (!swrContext) {
        printf("failed to create sampling context");
        goto __ERROR;
    }
    read_data_and_encode(fmt_ctx, c_ctx, swrContext, outfile);
    
    
__ERROR:
    if (swrContext) {
        swr_free(&swrContext);
    }
    
    if (c_ctx) {
        avcodec_free_context(&c_ctx);
    }
    if (fmt_ctx) {
        avformat_close_input(&fmt_ctx);
    }
    if (outfile) {
        fclose(outfile);
    }
    return;
}

int main(void) {
    rec_audio();
    return 0;
}
