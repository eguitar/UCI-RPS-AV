//Imports dependencies
import { SerialPort } from "serialport";
// const ReadLine  = require("@serialport/parser-readline");
import { ReadlineParser } from '@serialport/parser-readline';
//Define the serial port
const port = new SerialPort({
  path:"COM9",
  baudRate: 9600,
});

//Serial port parser
const parser = new ReadlineParser();
port.pipe(parser);

// //Read the data from serial port
parser.on("data", (line) => console.log(line));

// //Write data to serial port
port.write("Writing to port");
var inByte = port.read();
console.log(inByte);
console.log("Progress");