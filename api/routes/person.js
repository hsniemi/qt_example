const express = require('express');
const router = express.Router();
const person = require('../models/person_model');

router.get('/:id?',
 function(request, response) {
  if (request.params.id) {
    person.getById(request.params.id, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult[0]);
      }
    });
  } else {
    person.getAll(function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
  }
});


router.post('/', 
function(request, response) {
  person.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json("Person added");
    }
  });
});


router.delete('/:id', 
function(request, response) {
  person.delete(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


router.put('/:id', 
function(request, response) {
  person.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      console.log(dbResult);
      if(dbResult.affectedRows==1){
        response.json("Person updated");
      }
      else{
        response.json("Person does not exist");
      }
    }
  });
});

router.post('/money_action', 
function(request, response) {
  person.moneyAction(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult.affectedRows);
    }
  });
});
module.exports = router;