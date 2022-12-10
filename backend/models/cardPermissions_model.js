const db = require('../database');

const cardPermissions = {
    getById: function(id, callback){
        return db.query('select * from cardPermissions where permissionId=?', [id], callback);
    },
    getAll: function(callback){
        return db.query('select * from cardPermissions', callback);
    },
    add: function(add_data, callback){
        return db.query(
            'insert into cardPermissions (cardId,accountId) values(?,?)',
            [add_data.cardId, add_data.accountId],
            callback
        );
    },
    delete: function(id, callback){
        return db.query('delete from cardPermissions where permissionId=?', [id], callback);
    },
    update: function(id, update_data, callback){
        return db.query(
            'update cardPermissions set cardId=? accountId=? where permissionId=?',
            [update_data.cardId, update_data.accountId, id],
            callback
        );
    }
};
module.exports = cardPermissions;