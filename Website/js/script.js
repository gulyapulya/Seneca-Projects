function clear() {
  var inputs = document.querySelectorAll("input");
  inputs.innerHMTL = "";
}

function orderPrCheck() {
  if (document.getElementById("purpose-3").checked)
    document.getElementById("reveal-if-checked").style.display = "block";
  else document.getElementById("reveal-if-checked").style.display = "none";
}

function showRoses() {
  var rosesDivs = document.getElementsByClassName("roses");
  for (var i = 0; i < rosesDivs.length; i++) {
    rosesDivs[i].style.display = "block";
  }
  var bouquetsDivs = document.getElementsByClassName("bouquets");
  for (var j = 0; j < bouquetsDivs.length; j++) {
    bouquetsDivs[j].style.display = "none";
  }
}

function showBouquets() {
  var rosesDivs = document.getElementsByClassName("roses");
  for (var i = 0; i < rosesDivs.length; i++) {
    rosesDivs[i].style.display = "none";
  }
  var bouquetsDivs = document.getElementsByClassName("bouquets");
  for (var k = 0; k < bouquetsDivs.length; k++) {
    bouquetsDivs[k].style.display = "block";
  }
}

function showAll() {
  var rosesDivs = document.getElementsByClassName("roses");
  for (var i = 0; i < rosesDivs.length; i++) {
    rosesDivs[i].style.display = "block";
  }
  var bouquetsDivs = document.getElementsByClassName("bouquets");
  for (var l = 0; l < bouquetsDivs.length; l++) {
    bouquetsDivs[l].style.display = "block";
  }
}

clear();
orderPrCheck();
showRoses();
showBouquets();
showAll();
