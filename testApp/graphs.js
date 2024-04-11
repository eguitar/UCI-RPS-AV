//Imports dependencies
import { SerialPort } from "serialport";
import { ReadlineParser } from '@serialport/parser-readline';

var lineChartData1 = [{label: "Series 1", range: 'range-l',
values: [{time: 169808190, y:0}, {time: 1698908190, y: 20}, {time: 1698908190, y: 80}   ]}, ];
var myChart1;

//Define the serial port
const port = new SerialPort({
  path:"COM5",
  baudRate: 57600,
});

//Serial port parser
const parser = new ReadlineParser();
port.pipe(parser);

//Read the data from serial port
parser.on("data", (line) => {getAltitudeValue(line)} );

//Write data to serial port
port.write("Writing to port");

function getTimeValue() {
    var dateBuffer = new Date();
    var Time = dateBuffer.getTime();
    return Time;
  }

  // function getRandomValue() {
  //   var randomValue = Math.random() * 100;
  //   return randomValue;
  // }

  function getAltitudeValue(altitudestr) {
    var altitude = altitudestr.split(',')[0];
    console.log("Altitude: " + altitude);
    updateGraph(altitude);
  }

  function updateGraph(altitude) {
    var newLineChartData = [{time: getTimeValue(), y:altitude}];
    myChart1.push(newLineChartData);
  }
  