'use strict'

var filterSelect = document.querySelector("select#filter")
var snapshot = document.querySelector('button#snapshot');
var picture = document.querySelector('canvas#picture');

picture.width=640;
picture.height=480;

var videoplay = document.querySelector('video#player')

function getMediaStream(stream) {
    // var videoTrack = stream.getVideoTracks()[0];



    window.stream = stream;
    videoplay.srcObject = stream;
}

function handleError(err) {
    console.log("get error", err)
}

function start() {
    if(!navigator.mediaDevices ||
        !navigator.mediaDevices.getUserMedia){
 
         console.log('getUserMedia is not supported!');
         return;
     }else{
        var constraints = {
            video : {
                width: 640,
                height: 480,
                frameRate:15,
                facingMode:'environment' // user, left, right
            },
            audio : false,
        }
        navigator.mediaDevices.getUserMedia(constraints).then(getMediaStream).catch(handleError);
     }
}

filterSelect.onchange = function() {
    videoplay.className = filterSelect.value;
}

snapshot.onclick = function() {
    picture.className = filterSelect.value;
    picture.getContext('2d').drawImage(videoplay, 0, 0, picture.width, picture.height);
}

start();