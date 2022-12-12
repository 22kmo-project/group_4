const db = require('../database');
const bcrypt = require('bcryptjs');

const saltRounds = 10;

const card = {
    getById: function(id, callback){
        return db.query('select * from card where cardId=?', [id], callback);
    },
    getAll: function(callback){
        return db.query('select * from card', callback);
    },
    add: function(add_data, callback){
        bcrypt.hash(add_data.pin, saltRounds, function(err, hashPin){
            return db.query(
                'insert into card (cardId,pin,isCredit,personId,accountId) values(?,?,?,?,?)',
                [add_data.cardId, hashPin, add_data.isCredit, add_data.personId, add_data.accountId],
                callback
            );
        });
    },
    delete: function(id, callback){
        return db.query('delete from card where cardId=?', [id], callback);
    },
    update: function(id, update_data, callback){
        bcrypt.hash(update_data.pin, saltRounds, function(err, hashPin){
            return db.query(
                'update card set pin=?, isCredit=?, personId=?, accountId=? where cardId=?',
                [hashPin, update_data.isCredit, update_data.personId, update_data.accountId, id],
                callback
            );
        });
    },
    checkPin: function(cardId,callback){
        return db.query(
            'select pin from card where cardId=?',
            [cardId],
            callback
        )
    }
};
module.exports = card;