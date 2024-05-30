const mainImage = document.getElementById('mainImage');
let currentPagina = null;
let ondertitel = document.getElementById('ondertitelVeld');
let keuze_1 = document.getElementById('keuze-1');
let keuze_2 = document.getElementById('keuze-2');
let keuze_3 = document.getElementById('keuze-3');
let GekozenBedrag = "";
let pin = "";
let pogingen = 0;
let optie_1 ={            
    "50" : 0,
    "20" : 0,
    "10" : 0
};
let optie_2 ={            
    "50" : 0,
    "20" : 0,
    "10" : 0
};
let optie_3 ={            
    "50" : 0,
    "20" : 0,
    "10" : 0
};

const MAX_BEDRAG = 200;
const TE_PINNEN_BEDRAGEN = [10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200];

const back = 103;
const ok = 106;

class Pagina {
    constructor(name, image, TitelPagina) {
        this.name = name;
        this.image = image;
        this.TitelPagina = TitelPagina;
    }
}

// let con = mysql.createConnection({
//     host: "145.24.223.91",
//     user: "root",
//     password: "games123"
// });

// con.connect(function(err) {
//     if (err) throw err;
//     console.log("Connected!");
// });

const einde =           new Pagina("einde", 'GUI\\einde.png', true);
const bonKeuze =        new Pagina("bon-keuze", 'GUI\\bon-keuze.png', true)
const snelPinnen =      new Pagina("snelPinnen", 'GUI\\snel-pinnen.png', true);
const ongeldigBedrag =  new Pagina("ongeldigBedrag", 'GUI\\ongeldig-bedrag.png', true);
const biljetKeuze =     new Pagina("biljetKeuze", 'GUI\\biljet-keuze-menu.png', false); //-
const bedragKeuze =     new Pagina("bedragKeuze", 'GUI\\bedrag-keuze.png', true);
const geldOpnemen =     new Pagina("geldOpnemen", 'GUI\\geld-opnemen-menu.png', false);//- "ok" keuze is bedrag keuze
const saldo =           new Pagina("saldo", 'GUI\\saldo-pagina.png', true);
const OnvoldoendeSaldo =new Pagina("OnvoldoendeSaldo", 'GUI\\te-weinig-saldo.png', true);
const taal =            new Pagina("taal", 'GUI\\taal-keuze.png', false); //-
const hoofdMenu =       new Pagina("hoofdMenu", 'GUI\\hoofd-menu.png', false);//-
const PINinvoer =       new Pagina("PINinvoer", 'GUI\\inlog-pagina.png', true);
const start =           new Pagina("start", 'GUI\\welkom-pagina.png', true);

currentPagina = start;
mainImage.src = currentPagina.image;
ondertitel.style.opacity = 0;
keuze_1.style.opacity = 0;
keuze_2.style.opacity = 0;
keuze_3.style.opacity = 0;

function checkIBAN() {
    try{
        let sqlcheck = 'SELECT IBAN FROM banking';
        con.query(sqlcheck,function (_err, result) {
            if (result == IBAN){
                IBANcorrect = true;
            }
            if(result !== IBAN){
                IBANcorrect = false;
            }

        });
    }

    catch (err) {
        console.log(err);
        console.log("error locating table");
        // return 0;
    }

    IBANcorrect = false;
    if (IBAN.length == 18) {
        IBANcorrect = true; 
    }

    if (IBANcorrect) {
        if (currentPagina == start) {
            setPage(PINinvoer);
        }
    }else{
        setPage(einde);
    }
}

function checkSaldo(_amount) {
    return true;
    //check bij database
}

function setOndertitel(value) {
    ondertitel.setAttribute('value', value);
}

function clearSubtitle(value) {
    switch (value) {
        case "pin":
            pin = "";
            setOndertitel(pin);
            break;
        case "GekozenBedrag":
            GekozenBedrag = "";
            setOndertitel(GekozenBedrag);
        default:
            setOndertitel('');
            break;
    }
}

function setPin(n){
    n = n%200;
    if (n == 10) {
        clearSubtitle("pin");
    }else if (n == 11) {
        changePageTo(ok);
    }else{
        if (pin.length != 4) {
            pin += n.toString();
        }else{

        }
    }
    setOndertitel(pin.replace(/./g, '*'));
}

function setBedrag(n) {
    n = n%200;
    if (n == 10) {
        GekozenBedrag = GekozenBedrag.slice(0,-1);
    }else if (n == 11) {
        changePageTo(ok);
    }else{
        GekozenBedrag += n.toString();   
        if (parseInt(GekozenBedrag) > 200) {
            GekozenBedrag = "200";
        }
    }
    setOndertitel(GekozenBedrag);
}

function setPage(page){
    const loadingScreen = document.getElementById('loadingScreen');
    loadingScreen.classList.add('wipe-effect');
    setTimeout(function() {
        loadingScreen.classList.remove('wipe-effect');
        available = true;
    }, 2000);
    currentPagina = page;
    setTimeout(() => {mainImage.src = currentPagina.image},900);

    if (currentPagina == PINinvoer || currentPagina == bedragKeuze || currentPagina == bonKeuze || currentPagina == saldo) {
        setTimeout(() => {ondertitel.style.opacity = 1;}, 900);
    }else{
        setTimeout(() => {ondertitel.style.opacity = 0;}, 900);
    }
    
    if (currentPagina == taal){
        setTimeout(() => {document.getElementById("wip").style.opacity = "1"},900);
    } else {
        setTimeout(() => {document.getElementById("wip").style.opacity = "0"},900);
    }

    if (currentPagina != PINinvoer) {
        pin = '';
    }

    
    if (currentPagina == saldo) {
        // try{
        //     let sqlcheck = 'SELECT Balance FROM Account';
        //     con.query(sqlcheck,function (err, result) {
        //         if (result == saldo){
        //             IBANcorrect = true;
        //         }
        //         if(result !== saldo){
        //             IBANcorrect = false;
        //         }
    
        //     });
        // }
    
        // catch (err) {
        //     console.log(err);
        //     console.log("error");
        //     return 0;
        // }
        setOndertitel('1365') //check bij database
    }

    if (currentPagina == biljetKeuze) {
        setTimeout(() => {keuze_1.style.opacity = 1;}, 900);
        setTimeout(() => {keuze_2.style.opacity = 1;}, 900);
        setTimeout(() => {keuze_3.style.opacity = 1;}, 900);
        
        let keuze1 = document.getElementById("keuze1");
        let keuze2 = document.getElementById("keuze2");
        let keuze3 = document.getElementById("keuze3");


        let bedrag = parseInt(GekozenBedrag);
        let vijftig;
        let twintig;
        let tien;
    
        //keuze 1
        vijftig = Math.trunc(bedrag/50);
        twintig = Math.trunc((bedrag-(50*vijftig))/20);
        tien = (bedrag-(vijftig*50)-(20*twintig))/10;
        optieString = (vijftig) ? String(vijftig)+ ' x 50 ': "";
        optieString += (twintig) ? String(twintig)+ ' x 20 ': "";
        optieString += (tien) ? String(tien)+ ' x 10': "";

        keuze1.setAttribute('value', optieString);
        optie_1 = {
            "50" : vijftig,
            "20" : twintig,
            "10" : tien
        }
        
        //keuze 2
        twintig = Math.trunc(bedrag/20);
        tien = (bedrag-(20*twintig))/10;
        optieString = (twintig) ? String(twintig)+ ' x 20 ': "";
        optieString += (tien) ? String(tien)+ ' x 10': "";

        keuze2.setAttribute('value', optieString);
        optie_2 = {
            "50" : 0,
            "20" : twintig,
            "10" : tien
        }
        
        let tempBedrag = bedrag;

        vijftig = Math.floor(bedrag/80);
        twintig = Math.floor(bedrag/80+0.5);
        tien = (bedrag-vijftig*50-twintig*20)/10;
        optie_3 = {
            "50" : vijftig,
            "20" : twintig,
            "10" : tien
        }

        optieString = (vijftig) ? String(vijftig)+ ' x 50 ': "";
        optieString += (twintig) ? String(twintig)+ ' x 20 ': "";
        optieString += (tien) ? String(tien)+ ' x 10': "";

        keuze3.setAttribute('value', optieString);

    }else{
        setTimeout(() => {keuze_1.style.opacity = 0;}, 900);
        setTimeout(() => {keuze_2.style.opacity = 0;}, 900);
        setTimeout(() => {keuze_3.style.opacity = 0;}, 900);
    }

    if (currentPagina != bedragKeuze && currentPagina != bonKeuze && currentPagina != saldo) {
        clearSubtitle("GekozenBedrag");
    }

    if (currentPagina == einde) {
        pin = "";
        GekozenBedrag = "";
        setTimeout(() => {
            setPage(start)
        }, 11000);
    }
}

function changePageTo(option) {
        if (option == back) {
            switch (currentPagina) {
                case PINinvoer:
                    setPage(start);
                    break;
                case hoofdMenu:
                    setPage(start);
                    break;
                case taal:
                    setPage(hoofdMenu);
                    break;
                case saldo:
                    setPage(hoofdMenu);
                    break;
                case geldOpnemen:
                    setPage(hoofdMenu);
                    break;
                case bedragKeuze:
                    setPage(geldOpnemen);
                    break;
                case biljetKeuze:
                    setPage(bedragKeuze);
                    break;
                case ongeldigBedrag:
                    setPage(bedragKeuze);
                    break;
                case snelPinnen:
                    setPage(hoofdMenu);
                    break;
                case bonKeuze:
                    //bon printer NIET activeren
                    setPage(einde);
                case OnvoldoendeSaldo:
                    setPage(hoofdMenu);
                default:
                    break;
            }
        }else if (option == ok) {
            switch (currentPagina) {
                case PINinvoer:
                    pinCorrect = false //check bij database
                    if (pin.length == 4 || pinCorrect) {
                        setPage(hoofdMenu);
                        setPin(210);
                    }else if (pogingen == 2) {
                        setPage(start);
                        setPin(210);
                        pogingen = 0;
                    } else {
                        pogingen++;
                        setPin(210);
                        ondertitel.style.backgroundColor = "#ff0000";
                        setTimeout(() => {
                            ondertitel.style.backgroundColor = "#AEAEAE";
                        }, 100);
                    }
                    break;
                case saldo:
                    setPage(geldOpnemen);
                    break;
                case geldOpnemen:
                    setPage(bedragKeuze);
                    break;
                case bedragKeuze:
                    if (!TE_PINNEN_BEDRAGEN.includes(parseInt(GekozenBedrag))) {
                        setPage(ongeldigBedrag);
                    }else{
                        setPage(biljetKeuze);
                    }
                    break;
                case snelPinnen:
                    if (checkSaldo(70)) {
                        setPage(bonKeuze);
                    }else{
                        setPage(OnvoldoendeSaldo);
                    }
                    break;
                case hoofdMenu:
                    setPage(snelPinnen);
                case bonKeuze:
                    //bon printer activeren
                    setPage(einde);
                    break;
                case biljetKeuze:
                    writeSerial(1);
                    writeSerial(optie_3["50"]);
                    writeSerial(optie_3["20"]);
                    writeSerial(optie_3["10"]);
                    setPage(bonKeuze);
                    break;
                default:
                    break;
            }
        }else if (option == 101){
            switch (currentPagina) {
                case geldOpnemen:
                    GekozenBedrag = '10';
                    setOndertitel(GekozenBedrag);
                    if (checkSaldo(10)) {
                        setPage(bonKeuze);
                    }else{
                        setPage(OnvoldoendeSaldo);
                    }
                    break;
                default:
                    break;
            }

        }else if (option == 102){
            switch (currentPagina) {
                case hoofdMenu:
                    break;
                case geldOpnemen:
                    GekozenBedrag = '50';
                    setOndertitel(GekozenBedrag);
                    if (checkSaldo(parseInt(GekozenBedrag))) {
                        setPage(bonKeuze);
                    }else{
                        setPage(OnvoldoendeSaldo);
                    }
                    break;
                default:
                    break;
            }
        }else if (option == 104){
            switch (currentPagina) {
                case hoofdMenu:
                    setPage(saldo);
                    break;
                case geldOpnemen:
                    GekozenBedrag = '20';
                    setOndertitel(GekozenBedrag);
                    if (checkSaldo(parseInt(GekozenBedrag))) {
                        setPage(bonKeuze);
                    }
                    break;
                case biljetKeuze:
                    writeSerial(1);
                    writeSerial(optie_1["50"]);
                    writeSerial(optie_1["20"]);
                    writeSerial(optie_1["10"]);
                    setPage(bonKeuze);
                    break;
                default:
                    break;
            }
        }else if (option == 105){
            switch (currentPagina) {
                case hoofdMenu:
                    setPage(geldOpnemen);
                    break;
                case biljetKeuze:
                    writeSerial(1);
                    writeSerial(optie_2["50"]);
                    writeSerial(optie_2["20"]);
                    writeSerial(optie_2["10"]);
                    setPage(bonKeuze);
                    break;
                default:
                    break;
            }
        }
}