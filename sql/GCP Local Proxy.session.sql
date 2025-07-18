CREATE TABLE customer (
  customerID int NOT NULL AUTO_INCREMENT,
  firstName varchar(100) NOT NULL,
  lastName varchar(100) NOT NULL,
  email varchar(255) NOT NULL,
  userPassword varchar(255) NOT NULL,
  address varchar(255) DEFAULT NULL,
  city varchar(100) DEFAULT NULL,
  state varchar(100) DEFAULT NULL,
  zip_code varchar(20) DEFAULT NULL,
  phone_number varchar(20) DEFAULT NULL,
  PRIMARY KEY (customerID),
  UNIQUE KEY email (email)
);

CREATE TABLE staff (
  staffID int NOT NULL AUTO_INCREMENT,
  firstName varchar(100) NOT NULL,
  lastName varchar(100) NOT NULL,
  email varchar(255) NOT NULL,
  password_hash varchar(255) NOT NULL,
  role varchar(100) NOT NULL,
  hire_date date NOT NULL,
  phone_number varchar(20) DEFAULT NULL,
  salary decimal(10,2) NOT NULL DEFAULT '0.00',
  PRIMARY KEY (staffID),
  UNIQUE KEY email (email)
);

CREATE TABLE creditcards (
  cardID int NOT NULL AUTO_INCREMENT,
  customerID int NOT NULL,
  cardNumber varchar(255) NOT NULL,
  cardType varchar(50) DEFAULT NULL,
  expirationDate date NOT NULL,
  billingAddress varchar(255) DEFAULT NULL,
  PRIMARY KEY (cardID),
  UNIQUE KEY cardNumber (cardNumber),
  KEY customerID (customerID),
  CONSTRAINT creditcards_ibfk_1 FOREIGN KEY (customerID) REFERENCES customer (customerID)
);

CREATE TABLE vinyl_record (
  vinylID int NOT NULL AUTO_INCREMENT,
  title varchar(255) NOT NULL,
  artistID int NOT NULL,
  genre varchar(100) DEFAULT NULL,
  releaseYear int DEFAULT NULL,
  price decimal(10,2) NOT NULL,
  stockQuantity int NOT NULL DEFAULT '0',
  description text,
  PRIMARY KEY (vinylID),
  KEY artistID (artistID),
  CONSTRAINT vinyl_record_ibfk_1 FOREIGN KEY (artistID) REFERENCES artists (artistID)
);

CREATE TABLE transactions (
  transactionID int NOT NULL AUTO_INCREMENT,
  customerID int NOT NULL,
  vinylID int NOT NULL,
  quantity int NOT NULL,
  price_at_purchase decimal(10,2) NOT NULL,
  transactionDate timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  transactionStatus varchar(50) NOT NULL DEFAULT 'Completed',
  card_id int DEFAULT NULL,
  PRIMARY KEY (transactionID),
  KEY customerID (customerID),
  KEY vinylID (vinylID),
  CONSTRAINT transactions_ibfk_1 FOREIGN KEY (customerID) REFERENCES customer (customerID),
  CONSTRAINT transactions_ibfk_2 FOREIGN KEY (vinylID) REFERENCES vinyl_record (vinylID)
);