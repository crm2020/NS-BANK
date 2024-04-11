const mainImage = document.getElementById('mainImage');
let currentPagina = null;
let ondertitel = document.getElementById('textbox');
let timer;

const back = 3;
const ok = 6;

class Pagina {
    constructor(name, image, TitelPagina, linksTo, prevPagina) {
        this.name = name;
        this.image = image;
        this.TitelPagina = TitelPagina;
        this.linksTo = linksTo;
        this.prevPagina = prevPagina;
    }

    setLinks(page) {
        this.linksTo = page;
    }

    setPrev(page) {
        this.prevPagina = page;
    }
}

let einde =           new Pagina("einde", '', true);
let snelPinnen =      new Pagina("snelPinnen", 'GUI\\snel-pinnen.png', true);
let ongeldigBedrag =  new Pagina("ongeldigBedrag", 'GUI\\ongeldig-bedrag.png', true);
let biljetKeuze =     new Pagina("biljetKeuze", 'GUI\\biljet-keuze-menu.png', false); //-
let bedragKeuze =     new Pagina("bedragKeuze", 'GUI\\bedrag-keuze.png', true);
let geldOpnemen =     new Pagina("geldOpnemen", 'GUI\\geld-opnemen-menu.png', false);//- "ok" keuze is bedrag keuze
let saldo =           new Pagina("saldo", 'GUI\\saldo-pagina.png', true);
let taal =            new Pagina("taal", '', false); //-
let hoofdMenu =       new Pagina("hoofdMenu", 'GUI\\hoofd-menu.png', false);//-
let PINinvoer =       new Pagina("PINinvoer", 'GUI\\inlog-pagina.png', true);
let start =           new Pagina("start", 'GUI\\welkom-pagina.png', true);

einde.setLinks(start);
einde.setPrev(null);
snelPinnen.setLinks(einde);
snelPinnen.setPrev(hoofdMenu);
ongeldigBedrag.setLinks(null);
ongeldigBedrag.setPrev(bedragKeuze);
biljetKeuze.setLinks(einde);
biljetKeuze.setPrev(bedragKeuze);
bedragKeuze.setLinks(biljetKeuze);
bedragKeuze.setPrev(geldOpnemen);
geldOpnemen.setLinks(bedragKeuze);
geldOpnemen.setPrev(hoofdMenu);
saldo.setLinks(geldOpnemen);
saldo.setPrev(hoofdMenu);
taal.setLinks([null,null,null,null,null,null]);
taal.setPrev(hoofdMenu);
hoofdMenu.setLinks([taal,null,start,saldo,geldOpnemen,snelPinnen]);
hoofdMenu.setPrev(null);
PINinvoer.setLinks(hoofdMenu);
PINinvoer.setPrev(start);
start.setLinks(PINinvoer);
start.setPrev(null);

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

            default:
                break;
        }
    }


    // switch (currentPagina) {
    //     case start:
    //         setTimeout(() => {ondertitel.value = "****"},1000);
    //         currentPagina = PINinvoer;
    //         break;

    //     case PINinvoer:
    //         if(option == 1){
    //             currentPagina = currentPagina.linksTo;
    //         }
    //         setTimeout(() => {ondertitel.value = ""}, 1000);
    //         setTimeout(() => {ondertitel.style.opacity = 0}, 1000);
    //         break;
    
    //     default:
    //         break;
    // }
    if (!currentPagina.TitelPagina) {
        setTimeout(() => {ondertitel.style.opacity = 0;}, 900);
    }
    setTimeout(() => {mainImage.src = currentPagina.image},900);

    }, 120);

}

function pinBedrag(){

}