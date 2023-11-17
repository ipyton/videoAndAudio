'use strict'

var videoplay = document.querySelector('video#player')
var recvideo = document.querySelector('video#recplayer');
var btnRecord = document.querySelector('button#record');
var btnPlay = document.querySelector('button#recplay');
var btnDownload = document.querySelector('button#download');

var buffer;
var mediaRecorder;

function getMediaStream(stream){
    window.stream = stream
    videoplay.srcObject = stream
}

function handleError(err) {
    console.log('get user media', err)
}

function start() {
    if (!navigator.mediaDevices || !navigator.mediaDevices.getDisplayMedia) {
        console.log("get display media is not supported")
        return;
    } else {
        var constraints = {
            video : {
                width: 640,
                height: 480,
                frameRate: 15
            },
            audio : false
        }
        navigator.mediaDevices.getDisplayMedia(constraints).then(getMediaStream).catch(handleError);
    }
}

start();


function handleDataAvailable(e) {
    if (e && e.data && e.data.size > 0) {
        buffer.push(e.data)
    }
}

function startRecord() {
    buffer = []

    var options = {
        mimeType: 'video/webm;codecs=vp8'
    }

    if (!MediaRecorder.isTypeSupported(options.mimeType)) {
        console.error(`${options.mimeType} is not supported!`)
    }
    try {
        mediaRecorder = new MediaRecorder(window.stream, options)
    } catch(e) {
        console.error('Failed to create media recorder', e)
        return;
    }
    mediaRecorder.ondataavailable = handleDataAvailable
    mediaRecorder.start(10)
}

function stopRecord() {
    mediaRecorder.stop()
}

btnRecord.onclick = ()=>{
    if (btnRecord.textContent === "start") {
        startRecord();
        btnRecord.textContent = "stop";
        btnPlay.disabled = true;
        btnDownload.disabled = true;
    }
    else {
        stopRecord()
        btnRecord.textContent = "start"
        btnPlay.disabled = false;
        btnDownload.disabled = false;
    }
}

btnPlay.onclick = ()=>{
    var blob = new Blob(buffer, {type: 'video/webm'})
    recvideo.src = window.URL.createObjectURL(blob)
    recvideo.srcObject = null
    recvideo.controls = true
    recvideo.play()
}

btnDownload.onclick = ()=>{
    var blob = new Blob(buffer, {type: 'video/webm'})
    var url = window.URL.createObjectURL(blob)
    var a = document.createElement('a')

    a.href = url
    a.style.display = 'none'
    a.download = 'aaa.webm'
    a.click()
}