const mainImage = document.getElementById('mainImage');
let currentPagina = null;
let ondertitel = document.getElementById('textbox');
let GekozenBedrag = "";
let pin = "";
let pogingen = 0;

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

const einde =           new Pagina("einde", 'GUI\\einde.png', true);
const bonKeuze =        new Pagina("bon-keuze", 'GUI\\bon-keuze.png', true)
const snelPinnen =      new Pagina("snelPinnen", 'GUI\\snel-pinnen.png', true);
const ongeldigBedrag =  new Pagina("ongeldigBedrag", 'GUI\\ongeldig-bedrag.png', true);
const biljetKeuze =     new Pagina("biljetKeuze", 'GUI\\biljet-keuze-menu.png', false); //-
const bedragKeuze =     new Pagina("bedragKeuze", 'GUI\\bedrag-keuze.png', true);
const geldOpnemen =     new Pagina("geldOpnemen", 'GUI\\geld-opnemen-menu.png', false);//- "ok" keuze is bedrag keuze
const saldo =           new Pagina("saldo", 'GUI\\saldo-pagina.png', true);
const taal =            new Pagina("taal", 'GUI\\taal-keuze.png', false); //-
const hoofdMenu =       new Pagina("hoofdMenu", 'GUI\\hoofd-menu.png', false);//-
const PINinvoer =       new Pagina("PINinvoer", 'GUI\\inlog-pagina.png', true);
const start =           new Pagina("start", 'GUI\\welkom-pagina.png', true);

currentPagina = start;
mainImage.src = currentPagina.image;
ondertitel.style.opacity = 0;

function clearSubtitle(value) {
    switch (value) {
        case "pin":
            pin = "";
            ondertitel.setAttribute('value', '');
            break;
        case "GekozenBedrag":
            GekozenBedrag = "";
            ondertitel.setAttribute('value', '');
        default:
            ondertitel.setAttribute('value', '');
            break;
    }
}

function setPin(n){
    n = n%200;
    if (n == 10) {
        clearSubtitle("pin")
    }else if (n == 11) {
        changePageTo(ok);
    }else{
        if (pin.length != 4) {
            pin += n.toString();
        }else{

        }
    }
    ondertitel.setAttribute('value', pin.replace(/./g, '*'));
}

function setBedrag(n) {
    n = n%200;
    if (n == 10) {
        GekozenBedrag = GekozenBedrag.slice(0,-1);
    }else if (n == 11) {
        changePageTo(ok);
    }else{
        if (parseInt(GekozenBedrag) > 200) {
            GekozenBedrag = "200";
        }else{
            GekozenBedrag += n.toString();   
        }
    }
    ondertitel.setAttribute('value', GekozenBedrag);
}

function setPage(page){
    const loadingScreen = document.getElementById('loadingScreen');
    loadingScreen.classList.add('wipe-effect');
    setTimeout(function() {
        loadingScreen.classList.remove('wipe-effect');
        availilieble = true;
    }, 2000);
    currentPagina = page;
    setTimeout(() => {mainImage.src = currentPagina.image},900);
}

function changePageTo(option) {
        if (currentPagina == start){
            setPage(PINinvoer);
        }else if (option == back) {
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
                    //voeg biljetkeuze toe
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
                        document.getElementById("textbox").style.backgroundColor = "#ff0000";
                        setTimeout(() => {
                            document.getElementById("textbox").style.backgroundColor = "#AEAEAE";
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
                    //check saldo bij database
                    setPage(bonKeuze);
                    break;
                case hoofdMenu:
                    setPage(snelPinnen);
                case bonKeuze:
                    //bon printer activeren
                    setPage(einde);
                default:
                    break;
            }
        }else if (option == 101){
            switch (currentPagina) {
                case hoofdMenu:
                    setPage(taal);
                    break;
                case taal:
                    //todo
                    break;
                case geldOpnemen:
                    // check saldo bij database
                    GekozenBedrag = "10";
                    setPage(bonKeuze);
                    break;
                case biljetKeuze:
                    //niks
                    break;
                default:
                    break;
            }

        }else if (option == 102){
            switch (currentPagina) {
                case hoofdMenu:
                    break;
                case taal:
                    //todo
                    break;
                case geldOpnemen:
                    // check saldo bij database
                    GekozenBedrag = "50";
                    setPage(bonKeuze);
                    break;
                case biljetKeuze:
                    //niks
                    break;
                default:
                    break;
            }
        }else if (option == 104){
            switch (currentPagina) {
                case hoofdMenu:
                    // check saldo bij database
                    setPage(saldo);
                    break;
                case taal:
                    //todo
                    break;
                case geldOpnemen:
                    // check saldo bij database
                    GekozenBedrag = "20";
                    setPage(bonKeuze);
                    break;
                case biljetKeuze:
                    //biljet keuze toevoegen
                    break;
                default:
                    break;
            }
        }else if (option == 105){
            switch (currentPagina) {
                case hoofdMenu:
                    setPage(geldOpnemen);
                    break;
                case taal:
                    //todo
                    break;
                case geldOpnemen:
                    //niks
                    break;
                case biljetKeuze:
                    //biljet keuze toevoegen
                    break;
                default:
                    break;
            }
        }


        if (currentPagina == PINinvoer || currentPagina == bedragKeuze || currentPagina == bonKeuze) {
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
            setPin(210);
        }

        if (currentPagina != bedragKeuze && currentPagina != bonKeuze) {
            clearSubtitle("GekozenBedrag");
        }

        if (currentPagina == einde) {
            pin = "";
            GekozenBedrag = "";
            setTimeout(() => {
                setPage(start)
            }, 11000);
        }

        //debug
        document.getElementById("titel").innerText = currentPagina.name;
}