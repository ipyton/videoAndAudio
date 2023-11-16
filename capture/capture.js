'use strict';

var audioSource  = document.querySelector("select#audioSource");
var audioOutput  = document.querySelector("select#audioOutput");
var videoSource  = document.querySelector("select#videoSource");

const constraints = {
    video:{
        frameRate: {min:20},
        width: {min: 640, ideal: 1280},
        height: {min: 360, ideal: 720},
        aspectRatio: 16/9
    },
    audio:{
        echoCancellation: true,
        noiseSupression: true,
        autoGainControl: true
    },
};
const localVideo = document.querySelector('video')

function getLocalMediaStream(mediaStream) {
    console.log(localVideo)
    localVideo.srcObject = mediaStream;
}

function handleLocalMediaStreamError(error) {
    console.log("navigator.getMedia", error)
}

function getDevices(devicesInfo) {
    devicesInfo.forEach(element => {
        console.log(element.kind + ": label = " 
        + element.label + ": id = "
        + element.deviceId + ": groupId = "
        + element.groupId) 
    });
    var option = document.createElement('option')
    option.text = devicesInfo.label
    option.value = devicesInfo.deviceId
    if (devicesInfo.kind === 'audioinput') {
        audioSource.appendChild(option)
    }
    else if (devicesInfo.kind === 'audiooutput') {
        audioSource.appendChild(option)
    }
    else if (devicesInfo.kind === 'videoinput') {
        audioSource.appendChild(option)
    }
}

function enumerate_Device() {
    if (!navigator.mediaDevices || !navigator.mediaDevices.enumerateDevices) {
        console.log('enumerate devices are not supported')
    } else {
        console.log(navigator.mediaDevices.enumerateDevices())
        navigator.mediaDevices.enumerateDevices().then(getDevices).catch(handleLocalMediaStreamError)
    }

}

//deprecated because issues about privacy.
function capture(){
    navigator.mediaDevices.getUserMedia(constraints).then(
        getLocalMediaStream
    ).catch(handleLocalMediaStreamError)
}


function start(){
    (async () => {   
        await navigator.mediaDevices.getUserMedia({audio: true, video: true});   
        let devices = await navigator.mediaDevices.enumerateDevices();   
        console.log(devices); 
      })();
}

start()
