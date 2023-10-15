var meuValor = "HIGH"
var direção = "centro" // direita esquerda
function enviarESP8266 () {
  const url = "http://192.168.137.92/enviar";
  fetch(url, {
    method: "POST",
    headers: {
      "Content-Type": "application/x-www-form-urlencoded",
      },
      body: `valor=${meuValor}`,
  })
    .then((response) => {
      if (response.ok) {
        console.log("Valor enviado com sucesso para o ESP8266");
      } else {
          console.error("Erro ao enviar valor para o ESP8266");
        }
    })
      .catch((error) => {
        console.error("Erro na comunicação com o ESP8266", error);
      });
    }
function direçãoESP8266 () {
  const url = "http://192.168.137.92/direcao";
  fetch(url, {
    method: "POST",
    headers: {
      "Content-Type": "application/x-www-form-urlencoded",
    },
    body: `direcao=${direção}`,
  })
    .then((response) => {
      if (response.ok) {
        console.log("Valor enviado com sucesso para o ESP8266");
      } else {
        console.error("Erro ao enviar valor para o ESP8266");
      }
    })
      .catch((error) => {
          console.error("Erro na comunicação com o ESP8266", error);
      });
}
function Ligar() {
  meuValor = "HIGH"
  enviarESP8266()
}
function Desligar() {
  meuValor = "LOW"
  enviarESP8266()
}

function EPresionada(event) {
  console.log('A função foi chamada EPresionada')
  direção = 'e';
  direçãoESP8266()
}
function ELiberada(event) {
  console.log('A função foi chamada ELiberada')
  direção = 'c';
  direçãoESP8266()
}
function DPresionada(event) {
  console.log('A função foi chamada DPresionada')
  direção = 'd';
  direçãoESP8266()
}
function DLiberada(event) {
  console.log('A função foi chamada DLiberada') 
  direção = 'c';
  direçãoESP8266()
}