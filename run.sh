#!/bin/bash

echo 'Insert the accepted media types (media-type1,mediatype2,...):'

read var

program='./src/a.out '$var

eval $program
