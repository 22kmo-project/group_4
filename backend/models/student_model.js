const db = require('../database');

const student = {
    getById: function(id, callback){
        return db.query('select * from student where id_student=?', [id], callback);
    },
    getAll: function(callback){
        return db.query('select * from student', callback);
    },
    add: function(add_data, callback){
        return db.query(
            'insert into student (id_student,fname,lname,password) values(?,?,?,?)',
            [add_data.id_student, add_data.fname, add_data.lname, add_data.password],
            callback
        );
    },
    delete: function(id, callback){
        return db.query('delete from student where id_student=?', [id], callback);
    },
    update: function(id, update_data, callback){
        return db.query(
            'update student set fname=?, lname=?, password=? where id_student=?',
            [update_data.fname, update_data.lname, update_data.password, id],
            callback
        );
    }
};
module.exports = student;