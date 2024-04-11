const mainImage = document.getElementById('mainImage');
let currentPagina = null;

class Pagina {
    constructor(name, image, TitelPagina, linksTo, prevPagina){
        this.name = name;
        this.image = image;
        this.TitelPagina = TitelPagina;
        this.linksTo = linksTo;
        this.prevPagina = prevPagina;
    }
}

const einde =           new Pagina("einde", '', true, start, null);
const snelPinnen =      new Pagina("snelPinnen", 'GUI\\snel-pinnen.png', true, einde, hoofdMenu);
const ongeldigBedrag =  new Pagina("ongeldigBedrag", 'GUI\\ongeldig-bedrag.png', true, null, bedragKeuze);
const biljetKeuze =     new Pagina("biljetKeuze", 'GUI\\biljet-keuze-menu.png', false, einde, bedragKeuze);
const bedragKeuze =     new Pagina("bedragKeuze", 'GUI\\bedrag-keuze.png', true, biljetKeuze, geldOpnemen);
const geldOpnemen =     new Pagina("geldOpnemen", 'GUI\\geld-opnemen-menu.png', false, bedragKeuze, hoofdMenu);
const saldo =           new Pagina("saldo", 'GUI\\saldo-pagina.png', true, geldOpnemen,hoofdMenu );
const taal =            new Pagina("taal", '', false, [null,null,null,null,null,null], hoofdMenu);
const hoofdMenu =       new Pagina("hoofdMenu", 'GUI\\hoofd-menu.png', false, [taal,null,start,saldo,geldOpnemen,snelPinnen], null);
const PINinvoer =       new Pagina("PINinvoer", 'GUI\\inlog-pagina.png', true, hoofdMenu, start);
const start =           new Pagina("start", 'GUI\\welkom-pagina.png', true, PINinvoer, null);

currentPagina = start;
mainImage.src = currentPagina.image;


function changePageTo(option) {
    const mainImage = document.getElementById('mainImage');
    
    // if(currentPagina == start){
    //     currentPagina = PINinvoer;
    // } else if(){

    // }
    
    mainImage.src = currentPagina.image;
    console.log(currentPagina);
}

function pinBedrag(){

}