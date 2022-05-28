CREATE TABLE `Customer` (
	`id` INT NOT NULL AUTO_INCREMENT,
	`name` VARCHAR(255) NOT NULL,
	`phone` VARCHAR(255),
	`address` VARCHAR(255) NOT NULL,
	PRIMARY KEY (`id`)
);

CREATE TABLE `Order` (
	`order_id` INT NOT NULL AUTO_INCREMENT,
	`customer_id` INT NOT NULL,
	`product_id` INT NOT NULL,
	`quantity` INT NOT NULL,
	`total_price` FLOAT NOT NULL,
	`date` DATE NOT NULL,
	PRIMARY KEY (`order_id`)
);

CREATE TABLE `Product` (
	`product_id` INT NOT NULL AUTO_INCREMENT,
	`name` VARCHAR(255),
	`stock` INT NOT NULL,
	`price` FLOAT NOT NULL,
	PRIMARY KEY (`product_id`)
);

ALTER TABLE `Order` ADD CONSTRAINT `Order_fk0` FOREIGN KEY (`customer_id`) REFERENCES `Customer`(`id`);

ALTER TABLE `Order` ADD CONSTRAINT `Order_fk1` FOREIGN KEY (`product_id`) REFERENCES `Product`(`product_id`);




