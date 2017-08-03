// For an introduction to the Blank template, see the following documentation:
// http://go.microsoft.com/fwlink/?LinkID=397704
// To debug code on page load in cordova-simulate or on Android devices/emulators: launch your app, set breakpoints, 
// and then run "window.location.reload()" in the JavaScript Console.
(function () {
    "use strict";

    document.addEventListener( 'deviceready', onDeviceReady.bind( this ), false );

    //window.addEventListener("devicemotion", deviceMotionUpdate, true);


    //var pos = 0;
    //var last_a_x = 0;
    //var last_a_y = 0;
    //var last_a_z = 0;

    //var last_m_x = 0;
    //var last_m_y = 0;
    //var last_m_z = 0;

    //var last_g_x = 0;
    //var last_g_y = 0;
    //var last_g_z = 0;

    //var global_m_x = 0;
    //var global_m_y = 0;
    //var global_m_z = 0;

    //function deviceMotionUpdate(e) {

    //    var c = document.getElementById("char");
    //    var ctx = c.getContext("2d");

    //    var m_x = 0;
    //    var m_y = 0;
    //    var m_z = 0;

    //    var tmp_g_x = (e.accelerationIncludingGravity.x - e.acceleration.x) * 0.004;
    //    var tmp_g_y = (e.accelerationIncludingGravity.y - e.acceleration.y) * 0.004;
    //    var tmp_g_z = (e.accelerationIncludingGravity.z - e.acceleration.z) * 0.004;

    //    var g_x = Math.atan2(tmp_g_x, tmp_g_z) * 180 / Math.PI;
    //    var g_y = Math.atan2(tmp_g_y, tmp_g_z) * 180 / Math.PI;
    //    var g_z = 0;

    //    ctx.beginPath();
    //    ctx.moveTo(pos - 1, c.height / 4 + last_a_x);
    //    ctx.lineTo(pos, c.height / 4 + e.acceleration.x);
    //    ctx.strokeStyle = '#ff0000';
    //    ctx.stroke();


    //    ctx.beginPath();
    //    ctx.moveTo(pos - 1, c.height / 4 + last_a_y);
    //    ctx.lineTo(pos, c.height / 4 + e.acceleration.y);
    //    ctx.strokeStyle = '#00ff00';
    //    ctx.stroke();

    //    ctx.beginPath();
    //    ctx.moveTo(pos - 1, c.height / 4 + last_a_z);
    //    ctx.lineTo(pos, c.height / 4 + e.acceleration.z);
    //    ctx.strokeStyle = '#0000ff';
    //    ctx.stroke();




    //    ctx.beginPath();
    //    ctx.moveTo(pos - 1, c.height / 2 + last_m_x);
    //    ctx.lineTo(pos, c.height / 2 + global_m_x);
    //    ctx.strokeStyle = '#ff0000';
    //    ctx.stroke();


    //    ctx.beginPath();
    //    ctx.moveTo(pos - 1, c.height / 2 + last_m_y);
    //    ctx.lineTo(pos, c.height / 2 + global_m_y);
    //    ctx.strokeStyle = '#00ff00';
    //    ctx.stroke();

    //    ctx.beginPath();
    //    ctx.moveTo(pos - 1, c.height / 2 + last_m_z);
    //    ctx.lineTo(pos, c.height / 2 + global_m_z);
    //    ctx.strokeStyle = '#0000ff';
    //    ctx.stroke();





    //    ctx.beginPath();
    //    ctx.moveTo(pos - 1, (c.height - c.height / 4) - last_g_x);
    //    ctx.lineTo(pos, (c.height - c.height / 4) - g_x);
    //    ctx.strokeStyle = '#ff0000';
    //    ctx.stroke();


    //    ctx.beginPath();
    //    ctx.moveTo(pos - 1, (c.height - c.height / 4) - last_g_y);
    //    ctx.lineTo(pos, (c.height - c.height / 4) - g_y);
    //    ctx.strokeStyle = '#00ff00';
    //    ctx.stroke();

    //    ctx.beginPath();
    //    ctx.moveTo(pos - 1, (c.height - c.height / 4) - last_g_z);
    //    ctx.lineTo(pos, (c.height - c.height / 4) - g_z);
    //    ctx.strokeStyle = '#0000ff';
    //    ctx.stroke();


    //    last_a_x = e.acceleration.x;
    //    last_a_y = e.acceleration.y;
    //    last_a_z = e.acceleration.z;

    //    last_m_x = global_m_x;
    //    last_m_y = global_m_y;
    //    last_m_z = global_m_z;

    //    last_g_x = g_x;
    //    last_g_y = g_y;
    //    last_g_z = g_z;


    //    pos = pos + 1;

    //    if (pos >= c.width) {
    //        pos = 0;
    //        ctx.clearRect(0, 0, c.width, c.height);
    //    }

    //    //$("#A-x").html("X: " + e.accelerationIncludingGravity.x);
    //    //$("#A-y").html("Y: " + e.accelerationIncludingGravity.y);
    //    //$("#A-z").html("Z: " + e.accelerationIncludingGravity.z);
    //}

    function onDeviceReady() {
        //var c = document.getElementById("char");
        //var ctx = c.getContext("2d");
        //ctx.clearRect(0, 0, c.width, c.height);

        //var watchID = cordova.plugins.magnetometer.watchReadings(
        //    function success(reading) {
        //        global_m_x = reading.x;
        //        global_m_y = reading.y;
        //        global_m_z = reading.z;
        //    },
        //    function error(message) {
        //        console.log(message);
        //    }
        //)

        var net = require('net');
        alert("ok");


        //document.addEventListener( 'pause', onPause.bind( this ), false );
        //document.addEventListener( 'resume', onResume.bind( this ), false );

        //var start_x = 0;
        //var start_y = 0;
        //var start_z = 0;

        //var last_x = 0;
        //var last_y = 0;
        //var last_z = 0;

        //var pos_x = 0;
        //var pos_y = 0;
        //var pos_z = 0;

        //var time = 0;



        //function onSuccessA(acceleration) {
        //    var a_x = acceleration.x.toFixed(4) - start_x;
        //    var a_y = acceleration.y.toFixed(4) - start_y;
        //    var a_z = acceleration.z.toFixed(4) - start_z;

        //    if (last_y == a_y)
        //        time = time + 50;
        //    else {
        //        if (last_y != 0) {
        //            if (time == 0)
        //                pos_y = pos_y + (last_y * (50 / 1000) * (50 / 1000));
        //            else
        //                pos_y = pos_y + (last_y * (time / 1000) * (time / 1000));
        //        }
        //        time = 0;
        //    }

        //    last_y = a_y;

        //    $("#A-x-start").html("X: " + start_x);
        //    $("#A-y-start").html("Y: " + start_y);
        //    $("#A-z-start").html("Z: " + start_z);

        //    $("#A-x").html("X: " + a_x);
        //    $("#A-y").html("Y: " + a_y);
        //    $("#A-z").html("Z: " + a_z);

        //    $("#P-x").html("X: " + pos_x);
        //    $("#P-y").html("Y: " + pos_y);
        //    $("#P-z").html("Z: " + pos_z);
        //}

        //function onErrorA() {
        //    console.log('onError! A');
        //}

        //var watchIDA = navigator.accelerometer.watchAcceleration(onSuccessA, onErrorA, { frequency: 50 });

        //$("#start_calc_pos").click(function () {
        //    navigator.accelerometer.getCurrentAcceleration(
        //        function (acceleration) {
        //            start_x = acceleration.x.toFixed(4);
        //            start_y = acceleration.y.toFixed(4);
        //            start_z = acceleration.z.toFixed(4);
        //            pos_x = 0;
        //            pos_y = 0;
        //            pos_z = 0;
        //        },
        //        function () {
        //            alert("Error");
        //        }
        //    );
        //});


        //sensors.enableSensor("PROXIMITY");
        //alert(sensors.getValue());

        //$interval(function () {
        //    sensors.getState(function (values) {
        //        alert(values);
        //    });
        //}, 100);


    };

    //function onPause() {
    //    // TODO: This application has been suspended. Save application state here.
    //};

    //function onResume() {
    //    // TODO: This application has been reactivated. Restore application state here.
    //};
})();
