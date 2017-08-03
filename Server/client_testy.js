var net = require('net');
var lz4 = require("lz4js");


var client = new net.Socket();
client.connect(27015, '127.0.0.1', function() {
    console.log('Connected');
});

var p_t, a_t = 0;

client.on('data', function(data) {
    p_t = a_t;
    a_t = Date.now().valueOf();
    var delta_t = a_t - p_t;
    // console.log("Received: " + data + " time_delta: " + delta_t + "\n");
    //console.log(client.bufferSize);
    console.log(data.length);
    //console.log(lz4.decompress(data).length);
    //client.destroy();
});

// client.once("data",function(d){
//     console.log(d.length);
//     //client.destroy();
// });

client.on('close', function() {
    console.log('Connection closed');
    client.destroy();
});