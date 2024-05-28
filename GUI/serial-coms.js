let timer;
let waarde;
let availilieble = true;

let reader
let writer

let write;

function writeSerial(n) {
  write = n;
}

function HandleSerialInput() {
  if (waarde != NaN && waarde >= 100 && waarde < 112) {
    if (availilieble) {
      availilieble = false;
      changePageTo(waarde);
        setTimeout(function() {
          availible = true;
      }, 2000);
    }
  }else if (waarde >= 200 && waarde < 212) {
    if (currentPagina == PINinvoer) {
      setPin(waarde);
    }else if (currentPagina == bedragKeuze) {
      setBedrag(waarde);
    }
  }else if (waarde == 255) {
    console.log("Succes");
  }
}

document.getElementById('connectButton').addEventListener('click', async () => {
  document.getElementById('connectButton').style.display = "none";
  try {
    const port = await navigator.serial.requestPort();
    await port.open({ baudRate: 9600 });
    console.log('Serial port opened:', port);

    reader = port.readable.getReader();
    writer = port.writable.getWriter();

    while (true) {
      try {
        const { value, done } = await reader.read();
        if (done) {
          console.log('Stream has been closed by the device');
          break;
        }
        // ---------------------------------------------
        /*
        IBAN is tussen 48 en 90
        100 - 110 is knoppen
        200 - 212 is numpad
        */
        waarde = Number(value);
        console.log(waarde)
        if (waarde != NaN) {
          HandleSerialInput();
        }
        


        //----------------------------------------------
      } catch (err) {
        console.error('Error reading data:', err);
        break;
      }

      if (write) {
        try {
          await writer.write(new Uint8Array([write]));
        } catch (err) {
          console.error('Error reading data:', err);
          break;
        }
        write = NaN;
      }
    }
  } catch (err) {
    console.error('Error opening serial port:', err);
  }
});

