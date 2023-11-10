function dbInit()
{
    var db = LocalStorage.openDatabaseSync("Activity_DB", "", "Track exercise", 1000000)
    try {
        db.transaction(function (tx) {
            tx.executeSql('CREATE TABLE IF NOT EXISTS new_table (test_description text)')
        })
    } catch (err) {
        console.log("Error creating table in database: " + err)
    };
}

function dbGetHandle()
{
    try {
        var db = LocalStorage.openDatabaseSync("Activity_DB", "", "Track exercise", 1000000)
    } catch (err) {
        console.log("Error opening database: " + err)
    }
    return db
}

function dbInsert(Pdesc)
{
    var db = dbGetHandle()
    var rowid = 0;
    db.transaction(function (tx) {
        tx.executeSql('INSERT INTO new_table VALUES(?)', [Pdesc])
        var result = tx.executeSql('SELECT last_insert_rowid()')
        rowid = result.insertId
    })
    return rowid;
}

function dbReadAll()
{
    var db = dbGetHandle()
    db.transaction(function (tx) {
        var results = tx.executeSql(
                    'SELECT rowid,test_description FROM new_table')
        for (var i = 0; i < results.rows.length; i++) {
            listModel.append({
                                 row_id: results.rows.item(i).rowid,
                                 test_description: results.rows.item(i).test_description
                             })
        }
    })
}

function dbDelete(row_id)
{
    var db = dbGetHandle()
    db.transaction(function (tx) {
        tx.executeSql('DELETE FROM new_table WHERE rowid=?', [row_id])
    })
}
