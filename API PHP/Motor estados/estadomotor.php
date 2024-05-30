<?php
// Configurações do banco de dados
$servername = "localhost"; // endereço do servidor MySQL
$username = "root"; // nome de usuário do MySQL
$password = ""; // senha do MySQL
$dbname = "estado_motor"; // nome do banco de dados

// Conexão com o banco de dados
$conn = new mysqli($servername, $username, $password, $dbname);

// Verifica se a conexão foi bem sucedida
if ($conn->connect_error) {
    die("Conexão falhou: " . $conn->connect_error);
}

// Query para buscar o último valor inserido na tabela
$sql = "SELECT * FROM liga_desliga ORDER BY id DESC LIMIT 1";
$result = $conn->query($sql);

// Verifica se há resultados
if ($result->num_rows > 0) {
    // Converte os resultados em um array associativo
    $row = $result->fetch_assoc();
    
    // Retorna os dados em formato JSON
    header('Content-Type: application/json');
    echo json_encode($row);
} else {
    // Se não houver resultados, retorna um JSON vazio
    echo json_encode(array());
}

// Fecha a conexão com o banco de dados
$conn->close();
?>
