// Função para buscar e exibir os últimos horários inseridos
function fetchLatestSchedules() {
    fetch('http://192.168.100.102/dog/getinfo/get')
    .then(response => response.json())
    .then(data => {
        if (data.Horario1) {
            document.getElementById('latestHorario1').innerText = `Último Horário 1: ${data.Horario1.hora}:${data.Horario1.minuto}`;
        } else {
            document.getElementById('latestHorario1').innerText = 'Nenhum horário registrado para Horario1';
        }

        if (data.Horario2) {
            document.getElementById('latestHorario2').innerText = `Último Horário 2: ${data.Horario2.hora}:${data.Horario2.minuto}`;
        } else {
            document.getElementById('latestHorario2').innerText = 'Nenhum horário registrado para Horario2';
        }

        if (data.Horario3) {
            document.getElementById('latestHorario3').innerText = `Último Horário 3: ${data.Horario3.hora}:${data.Horario3.minuto}`;
        } else {
            document.getElementById('latestHorario3').innerText = 'Nenhum horário registrado para Horario3';
        }
    })
    .catch(error => {
        console.error('Erro:', error);
    });
}

// Chama a função para buscar os últimos horários inseridos ao carregar a página
window.onload = fetchLatestSchedules;
