const express = require("express");
const app = express();
const cors = require('cors');

// Definieeren van de netwerk poort.
const port = 8000;

// Zorg ervoor dat de server ook JSON berichten kan ontvangen
app.use(express.json());
app.use(cors());

//ter naar verzoeken op de eerder gedefinieerde netwerk poort.
app.listen(port, () => {
    console.log(`Server draait op http://localhost:${port}`);
})
app.get('/noob/api/health', (req, res) => {
    res.json({status: '200'});
})