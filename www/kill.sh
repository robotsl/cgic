#!/bin/bash
ps -aux | grep boa|awk '{print $2}'
