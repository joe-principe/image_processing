% Script file: grayscale.m
%
% Define variables:
%   img -- The image being loaded
%   gs1 -- The weighted grayscale image
%   gs2 -- The averaged grayscale image

% Clear the workspace
clc;
clear;

% Initialize the variables
img = imread("peppers.png");
gs1 = uint8(zeros(size(img,[1 2])));
gs2 = uint8(zeros(size(img,[1 2])));

% Convert to grayscale
for ii = 1:size(img,1)
    for jj = 1:size(img,2)
        gs1(ii, jj) = 0.299.*img(ii, jj, 1) + 0.587.*img(ii, jj, 2) ...
                  + 0.114.*img(ii, jj, 3);
        gs2(ii, jj) = img(ii, jj, 1) ./ 3 + img(ii, jj, 2) ./ 3 ...
                   + img(ii, jj, 3) ./ 3;
    end
end

% Display the images
subplot(1, 3, 1);
imshow(img(100:280, 160:340, :));
title("Original color image");

subplot(1, 3, 2);
imshow(gs1(100:280, 160:340));
title("Grayscale using weights");

subplot(1, 3, 3);
imshow(gs2(100:280, 160:340));
title("Grayscale using averaging");