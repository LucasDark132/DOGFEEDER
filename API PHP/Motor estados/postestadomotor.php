<?php
// Permitir solicitações de qualquer origem
header("Access-Control-Allow-Origin: *");

// Permitir os métodos GET, POST e OPTIONS
header("Access-Control-Allow-Methods: GET, POST, OPTIONS");

// Permitir os cabeçalhos especificados
header("Access-Control-Allow-Headers: Content-Type");

// Definir o tipo de conteúdo para JSON
header("Content-Type: application/json");

// Recebe o JSON enviado pelo JavaScript
$json = file_get_contents('php://input');

// Decodifica o JSON para um array associativo
$data = json_decode($json, true);

// Verifica se o JSON contém a chave "estado"
if (isset($data['estado'])) {
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

    // Obtém o valor do estado do JSON
    $estado = $data['estado'];

    // Query para atualizar o estado no banco de dados
    $sql = "UPDATE liga_desliga SET estado = $estado ORDER BY id DESC LIMIT 1";
    
    if ($conn->query($sql) === TRUE) {
        echo "Estado atualizado com sucesso.";
    } else {
        echo "Erro ao atualizar o estado: " . $conn->error;
    }

    // Fecha a conexão com o banco de dados
    $conn->close();
} else {
    echo "Erro: JSON inválido. O JSON deve conter a chave 'estado'.";
}
?>
