<?php
header('Content-Type: application/json');


// Permitir solicitações de qualquer origem
header("Access-Control-Allow-Origin: *");

// Permitir os métodos GET, POST e OPTIONS
header("Access-Control-Allow-Methods: GET, POST, OPTIONS");

// Permitir os cabeçalhos especificados
header("Access-Control-Allow-Headers: Content-Type");

// Definir o tipo de conteúdo para JSON
header("Content-Type: application/json");

$servername = "localhost";
$username = "root";
$password = "";
$dbname = "horariosDeAlimentacao";

// Criar conexão
$conn = new mysqli($servername, $username, $password, $dbname);

// Verificar conexão
if ($conn->connect_error) {
    die("Conexão falhou: " . $conn->connect_error);
}

$dados = array();

// Consulta SQL para obter o último valor inserido na tabela Horario1
$sql1 = "SELECT horaAlimentacao1 AS hora, minutoAlimentacao1 AS minuto FROM Horario1 ORDER BY Id DESC LIMIT 1";
$result1 = $conn->query($sql1);
if ($result1->num_rows > 0) {
    $dados['Horario1'] = $result1->fetch_assoc();
} else {
    $dados['Horario1'] = null;
}

// Consulta SQL para obter o último valor inserido na tabela Horario2
$sql2 = "SELECT horaAlimentacao2 AS hora, minutoAlimentacao2 AS minuto FROM Horario2 ORDER BY Id DESC LIMIT 1";
$result2 = $conn->query($sql2);
if ($result2->num_rows > 0) {
    $dados['Horario2'] = $result2->fetch_assoc();
} else {
    $dados['Horario2'] = null;
}

// Consulta SQL para obter o último valor inserido na tabela Horario3
$sql3 = "SELECT horaAlimentacao3 AS hora, minutoAlimentacao3 AS minuto FROM Horario3 ORDER BY Id DESC LIMIT 1";
$result3 = $conn->query($sql3);
if ($result3->num_rows > 0) {
    $dados['Horario3'] = $result3->fetch_assoc();
} else {
    $dados['Horario3'] = null;
}

$conn->close();

// Retornar os dados em formato JSON
echo json_encode($dados);
?>
