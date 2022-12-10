const db = require('../database');

const person = {
    getById: function(id, callback){
        return db.query('select * from person where personId=?', [id], callback);
    },
    getAll: function(callback){
        return db.query('select * from person', callback);
    },
    add: function(add_data, callback){
        return db.query(
            'insert into person (firstname,lastname) values(?,?)',
            [add_data.firstname, add_data.lastname],
            callback
        );
    },
    delete: function(id, callback){
        return db.query('delete from person where personId=?', [id], callback);
    },
    update: function(id, update_data, callback){
        return db.query(
            'update person set firstname=?, lastname=? where personId=?',
            [update_data.firstname, update_data.lastname, id],
            callback
        );
    }
};
module.exports = person;