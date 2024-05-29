let waarde;
let available = true;

let collectingIBAN = "";
let IBAN = "";

let reader
let writer


let write;
function writeSerial(n) {
  write = n;
}

function makeAvailable() {
  setTimeout(function() {
    available = true;
  }, 2000);
}

function HandleSerialInput() {
  if (waarde != NaN && waarde >= 100 && waarde < 112) {
    if (available) {
      available = false;
      changePageTo(waarde);
      makeAvailable();
    }
  }else if (waarde >= 200 && waarde < 212) {
    if (currentPagina == PINinvoer) {
      setPin(waarde);
    }else if (currentPagina == bedragKeuze) {
      setBedrag(waarde);
    }
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
        // console.log(value);
        waarde = Number(value);
        if (waarde != NaN && waarde > 99 && waarde < 213) {
          console.log(waarde)
          HandleSerialInput();
        }
        value.forEach(element => {
          // console.log(String.fromCharCode(element));
          if (element == 24) {
            console.log(waarde);
            setPage(start);
          }
          if (element >47 && element < 99) {
            collectingIBAN += String.fromCharCode(element);
          }
        });
        if (collectingIBAN.length == 18) {
          IBAN = collectingIBAN;
          console.log(IBAN);
          collectingIBAN = "";
          checkIBAN();
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

