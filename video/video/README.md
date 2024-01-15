# Foundamentals of Video and Audio.
This is a demo showing apis usage for ffmpeg.

There are three parts you need in audio recording process.
These are some parameters needed to be explain:
-----
codec_ctx->profile = FF_PROFILE_AAC_HE_V2 :specify the way the audio compress.
HE_V2 = AAC + SBR + PS;
AAC:Advanced Audio Coding.
SBR:Spectral Band Replication
PS:Parametric Stereo
    codec_ctx->profile
AAC FF_PROFILE_AAC_HE_V2
------
AV_SAMPLE_FMT_FLT presented by float32 [-1.0, 1.0]
AV_SAMPLE_FMT_S16 presented by int16 [-32767, +32767]
conversion rules: samplefmt.h
-----
