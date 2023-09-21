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

% Convert to grayscale
% for ii = 1:size(img,1)
%     for jj = 1:size(img,2)
%         gs1(ii, jj) = 0.299.*img(ii, jj, 1) + 0.587.*img(ii, jj, 2) ...
%                   + 0.114.*img(ii, jj, 3);
%         gs2(ii, jj) = img(ii, jj, 1) ./ 3 + img(ii, jj, 2) ./ 3 ...
%                    + img(ii, jj, 3) ./ 3;
%     end
% end

% Vectorized grayscaling
gs1 = 0.299 .* img(:,:,1) + 0.587 .* img(:,:,2) + 0.114 .* img(:,:,3);
gs2 = img(:,:,1) ./ 3 + img(:,:,2) ./ 3 + img(:,:,3) ./ 3;

% Write the grayscaled images out to file
% imwrite(gs1, "gs1_m.ppm");
% imwrite(gs2, "gs2_m.ppm");

% Display the images
subplot(1, 3, 1);
% imshow(img(100:280, 160:340, :));
imshow(img);
title("Original color image");

subplot(1, 3, 2);
% imshow(gs1(100:280, 160:340));
imshow(gs1);
title("Grayscale using weights");

subplot(1, 3, 3);
% imshow(gs2(100:280, 160:340));
imshow(gs2);
title("Grayscale using averaging");