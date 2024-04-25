const mainImage = document.getElementById('mainImage');
let currentPagina = null;
let ondertitel = document.getElementById('textbox');
let timer;
let geldAmount;

const back = 3;
const ok = 6;

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
ondertitel.style.opacity = 0;

function changePageTo(option) {
    clearTimeout(timer);
    timer = setTimeout(() =>{
    console.log('Received data:', option);
    const loadingScreen = document.getElementById('loadingScreen');
    loadingScreen.classList.add('wipe-effect');
    setTimeout(function() {
        loadingScreen.classList.remove('wipe-effect');
    }, 2000);

    if (currentPagina == start){
        currentPagina = PINinvoer;
    }else if (option == back) {
        switch (currentPagina) {
            case PINinvoer:
                currentPagina = start;
                break;
            case hoofdMenu:
                currentPagina = start;
                break;
            case taal:
                currentPagina = hoofdMenu;
                break;
            case saldo:
                currentPagina = hoofdMenu;
                break;
            case geldOpnemen:
                currentPagina = hoofdMenu;
                break;
            case bedragKeuze:
                currentPagina = geldOpnemen;
                break;
            case biljetKeuze:
                currentPagina = bedragKeuze;
                break;
            case ongeldigBedrag:
                currentPagina = bedragKeuze;
                break;
            case snelPinnen:
                currentPagina = hoofdMenu;
                break;

            default:
                break;
        }
    }else if (option == ok) {
        switch (currentPagina) {
            case PINinvoer:
                //check if pin is ok
                currentPagina = hoofdMenu;
                break;
            case saldo:
                currentPagina = geldOpnemen;
                break;
            case geldOpnemen:
                currentPagina = bedragKeuze;
                break;
            case bedragKeuze:
                //check if input amount is ok
                currentPagina = geldOpnemen;
                break;
            case snelPinnen:
                currentPagina = einde;
                break;
            case hoofdMenu:
                currentPagina = snelPinnen;
            default:
                break;
        }
    }else if (option == 1){
        switch (currentPagina) {
            case hoofdMenu:
                currentPagina = taal;
                break;
            case taal:
                //todo
                break;
            case geldOpnemen:
                geldAmount = 10;
                currentPagina = einde;
                break;
            case biljetKeuze:
                //niks
                break;
            default:
                break;
        }

    }else if (option == 2){
        switch (currentPagina) {
            case hoofdMenu:
                break;
            case taal:
                //todo
                break;
            case geldOpnemen:
                geldAmount = 10;
                currentPagina = einde;
                break;
            case biljetKeuze:
                //niks
                break;
            default:
                break;
        }
    }else if (option == 4){
        switch (currentPagina) {
            case hoofdMenu:
                currentPagina = saldo;
                break;
            case taal:
                //todo
                break;
            case geldOpnemen:
                geldAmount = 20;
                currentPagina = einde;
                break;
            case biljetKeuze:
                //biljet keuze toevoegen
                break;
            default:
                break;
        }
    }else if (option == 5){
        switch (currentPagina) {
            case hoofdMenu:
                currentPagina = geldOpnemen;
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
        document.getElementById("wip").style.opacity = "1";
    } else {
        document.getElementById("wip").style.opacity = "0";
    }
    
    setTimeout(() => {mainImage.src = currentPagina.image},900);

    document.getElementById("titel").innerText = currentPagina.name;
    }, 120);

}

function pinBedrag(){

}