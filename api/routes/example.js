const express = require('express');
const router = express.Router();
const example_sql = require('../models/example_model');

router.get('/allpersons',
    function(request,response){
        example_sql.getAllPersons(function(err,dbresult){
            if(err){
                response.json(err.errno);
            }
            else{
                console.log(dbresult);
                response.json(dbresult);
            }
        }
        )
    }
);

router.get('/oneperson/:id',
    function(request,response){
        example_sql.getOnePerson(request.params.id,
            function(err,dbresult){
                if(err){
                    response.json(err.errno);
                }
                else{
                    console.log(dbresult);
                    response.json(dbresult[0]);
                }
            })    
        }
);

router.get('/fullname/:id',
        function(request,response){
           example_sql.getfullName(request.params.id,
            function(err,dbresult){
                if(err){
                    response.json(err.errno);
                }
                else{
                    response.json(dbresult[0]);
                }
           })
        }
);

module.exports = router;