let timer;

let waarde;

let availilieble = true;


function HandleSerialInput() {
  if (waarde != NaN && waarde >= 100 && waarde < 112) {
    if (availilieble) {
      availilieble = false;
      changePageTo(waarde);
    }
  }else if (waarde >= 200 && waarde < 212) {
    if (currentPagina == PINinvoer) {
      setPin(waarde);
    }else if (currentPagina == bedragKeuze) {
      setBedrag(waarde);
    }
  }

  // if (!availible) {
  //   setTimeout(function() {
  //     availible = true;
  // }, 2000);
  // }
}

document.getElementById('connectButton').addEventListener('click', async () => {
  document.getElementById('connectButton').style.display = "none";
  try {
    const port = await navigator.serial.requestPort();
    await port.open({ baudRate: 9600 });
    console.log('Serial port opened:', port);

    const reader = port.readable.getReader();
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
        200 - 210 is numpad
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
    }
  } catch (err) {
    console.error('Error opening serial port:', err);
  }
});

