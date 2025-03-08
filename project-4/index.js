const express = require("express");
const http = require("http");
const path = require("path");
const { Server } = require("socket.io");

const app = express();
const server = http.createServer(app);
const io = new Server(server);

const PORT = 3333;

let arr = [];
let playingArray = [];

app.use(express.static(path.resolve("")));

app.get("/", (req, res) => {

    return res.sendFile("index.html");
});

io.on("connection", (socket) => {
    const clientIP = socket.handshake.address;
    console.log(`User connected from IP: ${clientIP}`);




    socket.on("find", (e) => { // Get name from client
        console.log(`User '${e.name}' is trying to find a game`);




        if (e.name != null) {
            arr.push(e.name); // Put name in array



            if (arr.length >= 2) {
                const p1name = arr[0];
                const p2name = arr[1];



                const p1obj = {
                    p1name: arr[0],
                    p1value: "X",
                    p1move: ""

                };



                const p2obj = {
                    p2name: arr[1],
                    p2value: "O",
                    p2move: ""
                };



                const obj = {
                    p1: p1obj,
                    p2: p2obj,
                    sum: 1
                };


                playingArray.push(obj);
                arr.splice(0, 2);
                console.log(`Players ${p1name} and ${p2name} matched to a game!`);
                io.emit("find", { allPlayers: playingArray }); // Send both player's info to client
            }
        }
    });

    socket.on("playing", (e) => {
        const { name, value, id } = e;
        
        const playerName = value === "X" ? playingArray.find(obj => obj.p1.p1name === name)?.p1.p1name : playingArray.find(obj => obj.p2.p2name === name)?.p2.p2name;

        console.log(`Received 'playing' event from player ${playerName} (${value}): ${id}`);
    

        const playerObj = value === "X" ? playingArray.find(obj => obj.p1.p1name === name) : playingArray.find(obj => obj.p2.p2name === name);

        if (playerObj) {
            if (value === "X") {
                playerObj.p1.p1move = id;
            } else if (value === "O") {
                playerObj.p2.p2move = id;
            }
            playerObj.sum++;
        }

        io.emit("playing", { allPlayers: playingArray });
    });

    socket.on("gameOver", (e) => {
        const { name } = e;
        const playerObj = playingArray.find(obj => obj.p1.p1name === name || obj.p2.p2name === name);
        
        if (playerObj) {
            let winner;
            let loser;
            if (playerObj.p1.p1name === name) {
                winner = playerObj.p2.p2name;
                loser = playerObj.p1.p1name;
            } else {
                winner = playerObj.p1.p1name;
                loser = playerObj.p2.p2name;
            }
    
            console.log(`Player ${winner} won against ${loser}`);
            playingArray = playingArray.filter(obj => obj.p1.p1name !== name && obj.p2.p2name !== name);
            console.log("Updated playingArray:", playingArray);
        } else {
        }
    });
});

server.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`);
});