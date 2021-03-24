const express = require('express');
const router = express.Router();
const example_sql = require('../models/example_model');

router.get('/allpersons',
    function(request,response){
        example_sql.getAllPersons(function(err,dbresult){
            if(err){
                response.json(err);
            }
            else{
                response.json(dbresult);
            }
        }
        )
    }
);

module.exports = router;