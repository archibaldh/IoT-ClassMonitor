const express = require('express');
const bodyParser = require('body-parser');
const path = require('path');
const ejs = require('ejs');

const app = express();
let soundValue;
let bgHue;

app.use(bodyParser.urlencoded({ extended: false }));
app.use(express.static(path.join(__dirname, 'public'), {
    setHeaders: (res, path, stat) => {
        res.set('Content-Type', 'application/javascript');
    }
}));

app.set('view engine', 'ejs');

app.post('/update', (req, res) => {
    if (req.body.sound) {
        soundValue = req.body.sound;
        console.log("Sound Level:", soundValue);
    } else {
        res.status(400).send("No data received");
    }
});

app.get('/api/soundValue', (req, res) => {
    res.json({ soundValue });
});

app.get('/index', (req, res) => {
    res.render('index', { soundValue: soundValue });
});

const PORT = 2467;
app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}/index`);
});