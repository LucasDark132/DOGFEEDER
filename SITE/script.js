var sETTIMEContainer = document.getElementById("sETTIMEContainer");
      if (sETTIMEContainer) {
        sETTIMEContainer.addEventListener("click", function (e) {
          window.location.href = "./Configtime.html";
        });
      }
      
      var frameSection3 = document.getElementById("frameSection3");
      if (frameSection3) {
        frameSection3.addEventListener("click", function (e) {
          window.location.href = "index.html";
        });
      }

      var FeedNOWLIGAR = document.getElementById("FeedNOWLIGAR");
      if (FeedNOWLIGAR) {
        FeedNOWLIGAR.addEventListener("click", function (e) {
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
    xhr.open("POST", "http://192.168.100.103/dog/motor/postestadomotor", true);

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