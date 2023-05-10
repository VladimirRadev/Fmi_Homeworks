<?php
    class Db {
        private $connection;
        public function __construct()
        {
            $this->connection= new PDO("mysql:host=localhost:3307;dbname=hw_3", "root", "");
        }
        public function getConnection() {
            return $this->connection;
        }

    }
?>