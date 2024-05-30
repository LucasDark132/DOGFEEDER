document.getElementById('feedingScheduleForm').addEventListener('submit', function(event) {
    event.preventDefault();

    const hora1 = document.getElementById('hora1').value;
    const minuto1 = document.getElementById('minuto1').value;
    const hora2 = document.getElementById('hora2').value;
    const minuto2 = document.getElementById('minuto2').value;
    const hora3 = document.getElementById('hora3').value;
    const minuto3 = document.getElementById('minuto3').value;

    const data = {
        horario1: { hora: parseInt(hora1), minuto: parseInt(minuto1) },
        horario2: { hora: parseInt(hora2), minuto: parseInt(minuto2) },
        horario3: { hora: parseInt(hora3), minuto: parseInt(minuto3) }
    };

    fetch('http://192.168.100.102/dog/insertinfo/insertdata', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(data)
    })
    .then(response => response.json())
    .then(data => {
        document.getElementById('response').innerText = data.message;
    })
    .catch(error => {
        console.error('Error:', error);
    });
});
