const db = require('../database');

const accountPermissions = {
    getById: function(id, callback){
        return db.query('select * from accountPermissions where permissionId=?', [id], callback);
    },
    getAll: function(callback){
        return db.query('select * from accountPermissions', callback);
    },
    add: function(add_data, callback){
        return db.query(
            'insert into accountPermissions (accountId,personId) values(?,?)',
            [add_data.accountId, add_data.personId],
            callback
        );
    },
    delete: function(id, callback){
        return db.query('delete from accountPermissions where permissionId=?', [id], callback);
    },
    update: function(id, update_data, callback){
        return db.query(
            'update accountPermissions set accountId=? personId=? where permissionId=?',
            [update_data.accountId, update_data.personId, id],
            callback
        );
    }
};
module.exports = accountPermissions;