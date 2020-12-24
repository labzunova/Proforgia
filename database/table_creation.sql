CREATE TABLE users (
	id serial primary key,
	nickname varchar(50) NOT NULL,
	UNIQUE (nickname),
	UNIQUE (email),
	email varchar(50) NOT NULL,
	create_time timestamp with time zone NOT NULL DEFAULT current_timestamp,
	password varchar(200) NOT NULL
);

CREATE TABLE rooms (
	id serial primary key,
	create_time timestamp with time zone NOT NULL DEFAULT current_timestamp,
	room_name varchar(100) NOT NULL,
	room_description varchar(1000)
);

CREATE TYPE rights AS ENUM ('admin', 'user');
CREATE TABLE users_to_rooms (
	user_id integer NOT NULL REFERENCES users ON DELETE CASCADE,
	room_id integer NOT NULL REFERENCES rooms ON DELETE CASCADE,
	PRIMARY KEY (user_id, room_id),
	user_rights rights DEFAULT 'user'
);

CREATE TABLE posts (
	id serial primary key,
	create_time timestamp with time zone NOT NULL DEFAULT current_timestamp,
	user_id integer NOT NULL REFERENCES users ON DELETE CASCADE,
	room_id integer REFERENCES rooms ON DELETE CASCADE,
	title varchar(100) NOT NULL,
	post_text text
);
alter table posts alter column room_id drop NOT NULL;

CREATE TYPE fileType AS ENUM ('image', 'file');
CREATE TABLE files (
	id serial primary key,
	post_id integer NOT NULL REFERENCES posts ON DELETE CASCADE,
	filename varchar(200) NOT NULL,
	filename_storage varchar(200) NOT NULL,
	UNIQUE(post_id, filename),
	file_type fileType NOT NULL DEFAULT 'file'
);

 CREATE TABLE sessions (
	id serial primary key, 
	session_id char(255) NOT NULL, 
	user_id integer NOT NULL REFERENCES users ON DELETE CASCADE, 
	UNIQUE(session_id),
	create_time timestamp with time zone NOT NULL DEFAULT current_timestamp
);

CREATE TABLE tags (
	id serial primary key,
	tag_name varchar(20) NOT NULL,
	room_id integer NOT NULL REFERENCES rooms ON DELETE CASCADE,
	UNIQUE (tag_name, room_id)
);

CREATE TABLE tags_to_posts (
	tag_id integer NOT NULL REFERENCES tags ON DELETE RESTRICT,
	post_id integer NOT NULL REFERENCES posts ON DELETE CASCADE,
	PRIMARY KEY (tag_id, post_id)
);
