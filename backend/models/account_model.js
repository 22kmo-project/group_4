const db = require('../database');

const account = {
    getById: function(id, callback){
        return db.query('select * from account where accountId=?', [id], callback);
    },
    getAll: function(callback){
        return db.query('select * from account', callback);
    },
    add: function(add_data, callback){
        return db.query(
            'insert into account (balance,limit,personId,cardId,externalUser,creditLimit) values(?,?,?,?,?,?)',
            [add_data.balance, add_data.limit, add_data.personId, add_data.cardId, add_data.externalUser, add_data.creditLimit],
            callback
        );
    },
    delete: function(id, callback){
        return db.query('delete from account where accountId=?', [id], callback);
    },
    update: function(id, update_data, callback){
        return db.query(
            'update account set balance=? limit=?, personId=?, cardId=?, externalUser=?, creditLimit=? where accountId=?',
            [update_data.balance, update_data.limit, update_data.personId, update_data.cardId, update_data.externalUser, update_data.creditLimit, id],
            callback
        );
    }
};
module.exports = account;