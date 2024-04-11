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
        const waarde = Number(value);
        if (waarde != NaN) {
          changePageTo(waarde);
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

