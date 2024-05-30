<?php
// Permitir solicitações de qualquer origem
header("Access-Control-Allow-Origin: *");

// Permitir os métodos GET, POST e OPTIONS
header("Access-Control-Allow-Methods: GET, POST, OPTIONS");

// Permitir os cabeçalhos especificados
header("Access-Control-Allow-Headers: Content-Type");

// Definir o tipo de conteúdo para JSON
header("Content-Type: application/json");

// Configurações do banco de dados
$servername = "localhost"; // endereço do servidor MySQL
$username = "root"; // nome de usuário do MySQL
$password = ""; // senha do MySQL
$dbname = "horariosdealimentacao"; // nome do banco de dados

// Conexão com o banco de dados
$conn = new mysqli($servername, $username, $password, $dbname);

// Verifica se a conexão foi bem sucedida
if ($conn->connect_error) {
    die(json_encode(array("error" => "Conexão falhou: " . $conn->connect_error)));
}

// Query para obter os valores de tempoalimentacao
$sql = "SELECT tempoalimentacao FROM tempo";
$result = $conn->query($sql);

// Inicializa um array para armazenar os resultados
$tempoalimentacaoArray = array();

if ($result->num_rows > 0) {
    // Percorre os resultados e adiciona ao array
    while ($row = $result->fetch_assoc()) {
        $tempoalimentacaoArray[] = $row['tempoalimentacao'];
    }
    // Retorna os valores em formato JSON
    echo json_encode($tempoalimentacaoArray);
} else {
    // Retorna uma mensagem de erro caso não haja resultados
    echo json_encode(array("error" => "Nenhum valor encontrado."));
}

// Fecha a conexão com o banco de dados
$conn->close();
?>
