import { SerialPort } from "serialport";
import { ReadlineParser } from '@serialport/parser-readline';

const port = new SerialPort({
    path:"COM9",
    baudRate: 9600,
  });

port.write('Port connection and write operation succesful', function(err) {
  if (err) {
    return console.log('Error on write: ', err.message)
  }
  console.log('message written')
})

// Open errors will be emitted as an error event
port.on('error', function(err) {
  console.log('Error: ', err.message)
});


const parser = new ReadlineParser();
port.pipe(parser);
parser.on("data", (line) => console.log(line));


port.write('Message Sent ')
port.write(Buffer.from('Message Sengt'))