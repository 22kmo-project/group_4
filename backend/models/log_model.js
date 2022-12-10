const db = require('../database');

const log = {
    getById: function(id, callback){
        return db.query('select * from log where logId=?', [id], callback);
    },
    getAll: function(callback){
        return db.query('select * from log', callback);
    },
    add: function(add_data, callback){
        return db.query(
            'insert into log (date,personId,accountId,cardId,amount) values(?,?,?,?,?)',
            [add_data.date, add_data.personId, add_data.accountId, add_data.cardId, add_data.amount],
            callback
        );
    },
    delete: function(id, callback){
        return db.query('delete from log where logId=?', [id], callback);
    },
    update: function(id, update_data, callback){
        return db.query(
            'update log set date=?, personId=?, accountId=?, cardId=?, amount=? where logId=?',
            [update_data.date, update_data.personId, update_data.accountId, update_data.cardId, update_data.amount, id],
            callback
        );
    }
};
module.exports = log;