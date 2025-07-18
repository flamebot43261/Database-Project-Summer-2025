-- CREATE TABLE customer (
--   customerID int NOT NULL AUTO_INCREMENT,
--   firstName varchar(100) NOT NULL,
--   lastName varchar(100) NOT NULL,
--   email varchar(255) NOT NULL,
--   userPassword varchar(255) NOT NULL,
--   address varchar(255) DEFAULT NULL,
--   city varchar(100) DEFAULT NULL,
--   state varchar(100) DEFAULT NULL,
--   zip_code varchar(20) DEFAULT NULL,
--   phone_number varchar(20) DEFAULT NULL,
--   PRIMARY KEY (customerID),
--   UNIQUE KEY email (email)
-- );

-- CREATE TABLE staff (
--   staffID int NOT NULL AUTO_INCREMENT,
--   firstName varchar(100) NOT NULL,
--   lastName varchar(100) NOT NULL,
--   email varchar(255) NOT NULL,
--   password_hash varchar(255) NOT NULL,
--   role varchar(100) NOT NULL,
--   hire_date date NOT NULL,
--   phone_number varchar(20) DEFAULT NULL,
--   salary decimal(10,2) NOT NULL DEFAULT '0.00',
--   PRIMARY KEY (staffID),
--   UNIQUE KEY email (email)
-- );

-- CREATE TABLE creditcards (
--   cardID int NOT NULL AUTO_INCREMENT,
--   customerID int NOT NULL,
--   cardNumber varchar(255) NOT NULL,
--   cardType varchar(50) DEFAULT NULL,
--   expirationDate date NOT NULL,
--   billingAddress varchar(255) DEFAULT NULL,
--   PRIMARY KEY (cardID),
--   UNIQUE KEY cardNumber (cardNumber),
--   KEY customerID (customerID),
--   CONSTRAINT creditcards_ibfk_1 FOREIGN KEY (customerID) REFERENCES customer (customerID)
-- );

-- CREATE TABLE vinyl_record (
--   vinylID int NOT NULL AUTO_INCREMENT,
--   title varchar(255) NOT NULL,
--   artistID int NOT NULL,
--   genre varchar(100) DEFAULT NULL,
--   releaseYear int DEFAULT NULL,
--   price decimal(10,2) NOT NULL,
--   stockQuantity int NOT NULL DEFAULT '0',
--   description text,
--   PRIMARY KEY (vinylID),
--   KEY artistID (artistID),
--   CONSTRAINT vinyl_record_ibfk_1 FOREIGN KEY (artistID) REFERENCES artists (artistID)
-- );

-- CREATE TABLE transactions (
--   transactionID int NOT NULL AUTO_INCREMENT,
--   customerID int NOT NULL,
--   vinylID int NOT NULL,
--   quantity int NOT NULL,
--   price_at_purchase decimal(10,2) NOT NULL,
--   transactionDate timestamp NULL DEFAULT CURRENT_TIMESTAMP,
--   transactionStatus varchar(50) NOT NULL DEFAULT 'Completed',
--   card_id int DEFAULT NULL,
--   PRIMARY KEY (transactionID),
--   KEY customerID (customerID),
--   KEY vinylID (vinylID),
--   CONSTRAINT transactions_ibfk_1 FOREIGN KEY (customerID) REFERENCES customer (customerID),
--   CONSTRAINT transactions_ibfk_2 FOREIGN KEY (vinylID) REFERENCES vinyl_record (vinylID)
-- );

-- Populate artists
INSERT INTO artists (artistName) VALUES
('The Beatles'),
('Pink Floyd'),
('Led Zeppelin'),
('Miles Davis');

-- Populate customer
INSERT INTO customer (firstName, lastName, email, userPassword, address, city, state, zip_code, phone_number) VALUES
('John', 'Doe', 'john.doe@example.com', 'password123', '123 Main St', 'Anytown', 'CA', '12345', '555-1234'),
('Jane', 'Smith', 'jane.smith@example.com', 'password456', '456 Oak Ave', 'Someville', 'NY', '54321', '555-5678');

-- Populate staff
INSERT INTO staff (firstName, lastName, email, password_hash, role, hire_date, phone_number, salary) VALUES
('Alice', 'Johnson', 'alice.j@vinylstore.com', 'hash1', 'Manager', '2023-01-15', '555-1111', 60000.00),
('Bob', 'Williams', 'bob.w@vinylstore.com', 'hash2', 'Sales Associate', '2023-03-20', '555-2222', 40000.00);

-- Populate creditcards
-- Note: Assumes customerIDs are 1 and 2 from the inserts above.
INSERT INTO creditcards (customerID, cardNumber, cardType, expirationDate, billingAddress) VALUES
(1, '1111222233334444', 'Visa', '2027-12-31', '123 Main St, Anytown, CA 12345'),
(2, '5555666677778888', 'MasterCard', '2026-10-31', '456 Oak Ave, Someville, NY 54321');

-- Populate vinyl_record
-- Note: Assumes artistIDs are 1, 2, 3, 4 from the inserts above.
INSERT INTO vinyl_record (title, artistID, genre, releaseYear, price, stockQuantity, description) VALUES
('Abbey Road', 1, 'Rock', 1969, 25.99, 50, 'The eleventh studio album by the English rock band the Beatles.'),
('The Dark Side of the Moon', 2, 'Progressive Rock', 1973, 29.99, 30, 'The eighth studio album by the English rock band Pink Floyd.'),
('Led Zeppelin IV', 3, 'Hard Rock', 1971, 27.50, 40, 'The untitled fourth studio album by the English rock band Led Zeppelin.'),
('Kind of Blue', 4, 'Jazz', 1959, 22.00, 60, 'A studio album by American jazz trumpeter Miles Davis.');

-- Populate transactions
-- Note: Assumes customerIDs and vinylIDs from the inserts above.
INSERT INTO transactions (customerID, vinylID, quantity, price_at_purchase, transactionStatus, card_id) VALUES
(1, 1, 1, 25.99, 'Completed', 1),
(2, 2, 1, 29.99, 'Completed', 2),
(1, 4, 2, 22.00, 'Completed', 1);