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
        console.log('Received data:', Number(value));
        changePageTo(Number(value));

        // if (Number(value)){
        //   const p = document.getElementById('text');
        //   p.style.opacity = 1;
        // }else{
        //   const p = document.getElementById('text');
        //   p.style.opacity = 0;
        // }


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