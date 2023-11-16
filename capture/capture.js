'use strict';
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

navigator.mediaDevices.getUserMedia(constraints).then(
    getLocalMediaStream
).catch(handleLocalMediaStreamError)
