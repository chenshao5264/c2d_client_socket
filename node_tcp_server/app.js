let net      = require('net');
let readline = require('readline-sync');

net.createServer(function(socket) {
    console.log("new connection!");
    socket.write("I am TCP Server!")
    

    socket.on('data', function(data) {
       console.log(data.toString('utf8'))
       
      socket.write(data);
    });



}).listen(3000)