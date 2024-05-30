<?php
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Headers: Content-Type");
header("Content-Type: application/json");

$servername = "localhost";
$username = "root";  // substitua pelo seu usuário do MySQL
$password = "";  // substitua pela sua senha do MySQL
$dbname = "horariosdealimentacao";

// Cria a conexão
$conn = new mysqli($servername, $username, $password, $dbname);

// Verifica a conexão
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Lê os dados JSON enviados pelo cliente
$data = json_decode(file_get_contents("php://input"), true);

if (isset($data['horario1']) && isset($data['horario2']) && isset($data['horario3'])) {
    $horario1 = $data['horario1'];
    $horario2 = $data['horario2'];
    $horario3 = $data['horario3'];

    $horaAlimentacao1 = $horario1['hora'];
    $minutoAlimentacao1 = $horario1['minuto'];

    $horaAlimentacao2 = $horario2['hora'];
    $minutoAlimentacao2 = $horario2['minuto'];

    $horaAlimentacao3 = $horario3['hora'];
    $minutoAlimentacao3 = $horario3['minuto'];

    $sql1 = "INSERT INTO Horario1 (horaAlimentacao1, minutoAlimentacao1) VALUES ($horaAlimentacao1, $minutoAlimentacao1)";
    $sql2 = "INSERT INTO Horario2 (horaAlimentacao2, minutoAlimentacao2) VALUES ($horaAlimentacao2, $minutoAlimentacao2)";
    $sql3 = "INSERT INTO Horario3 (horaAlimentacao3, minutoAlimentacao3) VALUES ($horaAlimentacao3, $minutoAlimentacao3)";

    if ($conn->query($sql1) === TRUE && $conn->query($sql2) === TRUE && $conn->query($sql3) === TRUE) {
        echo json_encode(["message" => "Dados inseridos com sucesso!"]);
    } else {
        echo json_encode(["message" => "Erro ao inserir dados: " . $conn->error]);
    }
} else {
    echo json_encode(["message" => "Dados inválidos"]);
}

$conn->close();
?>
