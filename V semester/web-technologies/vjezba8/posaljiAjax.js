var porukaElement,brojPokusajaElement;
var pokusaj;
window.onload=function(){
   porukaElement=document.getElementById("poruka");
   brojPokusajaElement=document.getElementById("brojPokusaja");
   pokusaj=document.getElementById("pokusaj");
   pokusajAjax(null,ispisi);
   document.getElementById("posalji").addEventListener("click",function(){pokusajAjax(pokusaj.value,ispisi);})
}
function ispisi(poruka,brojPokusaja){
   porukaElement.innerHTML=poruka;
   brojPokusajaElement.innerHTML=brojPokusaja;
}
function pokusajAjax(pokusaj,fnCallback){
   var ajax = new XMLHttpRequest();
   ajax.onreadystatechange = function() {// Anonimna funkcija
       if (ajax.readyState == 4 && ajax.status == 200){
           var jsonRez = JSON.parse(ajax.responseText);
           ispisi(jsonRez.pokusaj.poruka,jsonRez.pokusaj.broj_pokusaja);
       }
       else if (ajax.readyState == 4)
           ispisi(ajax.statusText,null);
   }
   ajax.open("POST","http://localhost:3000",true);
   ajax.setRequestHeader("Content-Type", "application/json");
   ajax.send(JSON.stringify({pokusaj:pokusaj}));
}
