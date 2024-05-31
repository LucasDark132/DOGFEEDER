var registerschedules = document.getElementById("feed-buttons-parent");
      if (registerschedules) {
        registerschedules.addEventListener("click", function (e) {
          window.location.href = "./configure.html";
        });
      }

      var homecontainer = document.getElementById("home-container");
        if (homecontainer) {
          homecontainer.addEventListener("click", function (e) {
          window.location.href = "./index.html";
        });
        }

var frameparent2 = document.getElementById("frame-parent2");
if (frameparent2) {
  frameparent2.addEventListener("click", function (e) {
    enviarEstado(1); // Envia o valor "1" para a função enviarEstado
  });
}


      function enviarEstado(estado) {
    // Cria um objeto JavaScript com o estado
    var jsonData = { "estado": estado };

    // Converte o objeto JavaScript para JSON
    var jsonString = JSON.stringify(jsonData);

    // Cria uma instância de XMLHttpRequest
    var xhr = new XMLHttpRequest();
    
    // Define a URL e o método de requisição
    xhr.open("POST", "http://192.168.100.103:8080/dog/motor/postestadomotor", true);

    // Configura o cabeçalho da requisição
    xhr.setRequestHeader("Content-type", "application/json");

    // Define a função a ser chamada quando a resposta for recebida
    xhr.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            // Exibe a resposta do servidor
            console.log(this.responseText);
        }
    };

    // Envia a requisição com o JSON como corpo da requisição
    xhr.send(jsonString);
}

