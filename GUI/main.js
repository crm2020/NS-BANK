const mainImage = document.getElementById('mainImage');
let currentPagina = null;
let ondertitel = document.getElementById('textbox');
let timer;
let geldAmount;
let pin = "";

const back = 103;
const ok = 106;

class Pagina {
    constructor(name, image, TitelPagina, linksTo, prevPagina) {
        this.name = name;
        this.image = image;
        this.TitelPagina = TitelPagina;
    }
}

let einde =           new Pagina("einde", 'GUI\\einde.png', true);
let snelPinnen =      new Pagina("snelPinnen", 'GUI\\snel-pinnen.png', true);
let ongeldigBedrag =  new Pagina("ongeldigBedrag", 'GUI\\ongeldig-bedrag.png', true);
let biljetKeuze =     new Pagina("biljetKeuze", 'GUI\\biljet-keuze-menu.png', false); //-
let bedragKeuze =     new Pagina("bedragKeuze", 'GUI\\bedrag-keuze.png', true);
let geldOpnemen =     new Pagina("geldOpnemen", 'GUI\\geld-opnemen-menu.png', false);//- "ok" keuze is bedrag keuze
let saldo =           new Pagina("saldo", 'GUI\\saldo-pagina.png', true);
let taal =            new Pagina("taal", 'GUI\\taal-keuze.png', false); //-
let hoofdMenu =       new Pagina("hoofdMenu", 'GUI\\hoofd-menu.png', false);//-
let PINinvoer =       new Pagina("PINinvoer", 'GUI\\inlog-pagina.png', true);
let start =           new Pagina("start", 'GUI\\welkom-pagina.png', true);

currentPagina = start;
mainImage.src = currentPagina.image;
ondertitel.style.opacity = 1;

function setPin(n){
    n = n%200

    if (n == 10) {
        
    }

    n += n.toString();
    
}

function setPage(page){
    const loadingScreen = document.getElementById('loadingScreen');
    loadingScreen.classList.add('wipe-effect');
    setTimeout(function() {
        loadingScreen.classList.remove('wipe-effect');
    }, 2000);
    currentPagina = page;
    setTimeout(() => {mainImage.src = currentPagina.image},900);

}

function changePageTo(option) {
    clearTimeout(timer);
    timer = setTimeout(() =>{
    console.log('Received data:', option);

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
                setPage(bedragKeuze);
                break;
            case ongeldigBedrag:
                setPage(bedragKeuze);
                break;
            case snelPinnen:
                setPage(hoofdMenu);
                break;

            default:
                break;
        }
    }else if (option == ok) {
        switch (currentPagina) {
            case PINinvoer:
                //check if pin is ok
                setPage(hoofdMenu);
                break;
            case saldo:
                setPage(geldOpnemen);
                break;
            case geldOpnemen:
                setPage(bedragKeuze);
                break;
            case bedragKeuze:
                //check if input amount is ok
                setPage(geldOpnemen);
                break;
            case snelPinnen:
                setPage(einde);
                break;
            case hoofdMenu:
                setPage(snelPinnen);
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
                geldAmount = 10;
                setPage(einde);
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
                geldAmount = 10;
                setPage(einde);
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
                setPage(saldo);
                break;
            case taal:
                //todo
                break;
            case geldOpnemen:
                geldAmount = 20;
                setPage(einde);
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


    if (!currentPagina.TitelPagina) {
        setTimeout(() => {ondertitel.style.opacity = 0;}, 900);
    }
    
    if (currentPagina == taal){
        setTimeout(() => {document.getElementById("wip").style.opacity = "1"},900);
    } else {
        setTimeout(() => {document.getElementById("wip").style.opacity = "0"},900);
    }

    if (currentPagina == einde) {
        setTimeout(() => {
            setPage(start)
        }, 11000);
    }

    //debug
    document.getElementById("titel").innerText = currentPagina.name;
    }, 120);

}